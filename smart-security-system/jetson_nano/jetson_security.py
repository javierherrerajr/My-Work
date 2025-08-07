#!/usr/bin/env python3
"""
Jetson Nano Security System
Performs real-time person detection and sends alerts to the main security system
"""

import cv2
import torch
import numpy as np
import requests
import json
import time
import threading
from datetime import datetime
import argparse
import logging
from pathlib import Path

# Set up logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class JetsonSecuritySystem:
    def __init__(self, server_url, confidence_threshold=0.5, person_class_id=0):
        """
        Initialize Jetson Security System
        
        Args:
            server_url: URL of the main security system (e.g., "http://192.168.1.100:8080")
            confidence_threshold: Minimum confidence for person detection
            person_class_id: YOLO class ID for person (0 = person)
        """
        self.server_url = server_url
        self.confidence_threshold = confidence_threshold
        self.person_class_id = person_class_id
        self.last_detection_time = 0
        self.detection_cooldown = 3  # seconds between detections
        
        # Initialize camera
        self.camera = None
        self.is_running = False
        
        # Load YOLOv5 model
        self.model = None
        self.load_model()
        
        # Detection statistics
        self.total_detections = 0
        self.authorized_count = 0
        self.unauthorized_count = 0
    
    def load_model(self):
        """Load YOLOv5 model"""
        try:
            logger.info("Loading YOLOv5 model...")
            # Load YOLOv5s model (small, fast for Jetson Nano)
            self.model = torch.hub.load('ultralytics/yolov5', 'yolov5s', pretrained=True)
            
            # Set model to evaluation mode
            self.model.eval()
            
            # Configure for Jetson Nano (use CPU if GPU not available)
            device = 'cuda' if torch.cuda.is_available() else 'cpu'
            self.model.to(device)
            
            logger.info(f"YOLOv5 model loaded successfully on {device}")
            
        except Exception as e:
            logger.error(f"Failed to load YOLOv5 model: {e}")
            raise
    
    def initialize_camera(self, camera_index=0):
        """Initialize camera"""
        try:
            logger.info(f"Initializing camera {camera_index}...")
            
            # Try different backends for Jetson
            backends = [cv2.CAP_GSTREAMER, cv2.CAP_V4L2, cv2.CAP_ANY]
            
            for backend in backends:
                self.camera = cv2.VideoCapture(camera_index, backend)
                if self.camera.isOpened():
                    logger.info(f"Camera opened with backend {backend}")
                    break
                self.camera.release()
            
            if not self.camera.isOpened():
                raise Exception(f"Could not open camera {camera_index}")
            
            # Set camera properties for optimal performance
            self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
            self.camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
            self.camera.set(cv2.CAP_PROP_FPS, 15)  # Lower FPS for Jetson Nano
            self.camera.set(cv2.CAP_PROP_BUFFERSIZE, 1)
            
            logger.info("Camera initialized successfully")
            
        except Exception as e:
            logger.error(f"Failed to initialize camera: {e}")
            raise
    
    def detect_persons(self, frame):
        """
        Detect persons in frame using YOLOv5
        
        Returns:
            List of detection dictionaries with bounding boxes and confidence
        """
        try:
            # Run inference
            results = self.model(frame)
            
            # Extract detections
            detections = results.pandas().xyxy[0]  # Get pandas DataFrame
            
            # Filter for person detections above confidence threshold
            person_detections = detections[
                (detections['class'] == self.person_class_id) & 
                (detections['confidence'] >= self.confidence_threshold)
            ]
            
            # Convert to list of dictionaries
            detection_list = []
            for _, detection in person_detections.iterrows():
                detection_list.append({
                    'bbox': [detection['xmin'], detection['ymin'], detection['xmax'], detection['ymax']],
                    'confidence': detection['confidence'],
                    'class': 'person'
                })
            
            return detection_list
            
        except Exception as e:
            logger.error(f"Error in person detection: {e}")
            return []
    
    def send_detection_alert(self, detection_type, confidence):
        """
        Send detection alert to main security system
        
        Args:
            detection_type: "authorized" or "unauthorized"
            confidence: Detection confidence score
        """
        try:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            data = {
                'person_type': detection_type,
                'confidence': float(confidence),
                'timestamp': timestamp,
                'device': 'jetson_nano',
                'location': 'main_entrance'  # Configure as needed
            }
            
            response = requests.post(
                self.server_url,
                json=data,
                timeout=5,
                headers={'Content-Type': 'application/json'}
            )
            
            if response.status_code == 200:
                logger.info(f"Alert sent successfully: {detection_type} ({confidence:.2f})")
                self.total_detections += 1
                if detection_type == "authorized":
                    self.authorized_count += 1
                else:
                    self.unauthorized_count += 1
            else:
                logger.warning(f"Failed to send alert: HTTP {response.status_code}")
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Network error sending alert: {e}")
        except Exception as e:
            logger.error(f"Error sending detection alert: {e}")
    
    def classify_person(self, detection):
        """
        Classify if detected person is authorized or unauthorized
        
        For this simple version, we'll use a placeholder.
        In production, you could:
        1. Use face recognition
        2. Use person re-identification
        3. Use time-based rules
        4. Use location-based rules
        
        Args:
            detection: Detection dictionary with bbox and confidence
            
        Returns:
            "authorized" or "unauthorized"
        """
        # Placeholder logic - customize based on your needs
        confidence = detection['confidence']
        
        # Simple rule: High confidence detections during business hours = authorized
        # Low confidence or after hours = unauthorized
        current_hour = datetime.now().hour
        
        if 8 <= current_hour <= 18 and confidence > 0.8:
            return "authorized"
        else:
            return "unauthorized"
    
    def process_frame(self, frame):
        """Process a single frame for person detection"""
        # Detect persons
        detections = self.detect_persons(frame)
        
        if detections:
            current_time = time.time()
            
            # Only process if cooldown period has passed
            if current_time - self.last_detection_time >= self.detection_cooldown:
                # Get the highest confidence detection
                best_detection = max(detections, key=lambda x: x['confidence'])
                
                # Classify the person
                person_type = self.classify_person(best_detection)
                
                # Send alert
                self.send_detection_alert(person_type, best_detection['confidence'])
                
                self.last_detection_time = current_time
                
                # Draw bounding box for visualization
                bbox = best_detection['bbox']
                color = (0, 255, 0) if person_type == "authorized" else (0, 0, 255)
                cv2.rectangle(frame, (int(bbox[0]), int(bbox[1])), (int(bbox[2]), int(bbox[3])), color, 2)
                cv2.putText(frame, f"{person_type} ({best_detection['confidence']:.2f})", 
                           (int(bbox[0]), int(bbox[1])-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
        
        return frame
    
    def start_monitoring(self, camera_index=0, show_video=False):
        """Start the security monitoring system"""
        try:
            # Initialize camera
            self.initialize_camera(camera_index)
            
            self.is_running = True
            logger.info("Starting security monitoring...")
            logger.info(f"Server URL: {self.server_url}")
            logger.info(f"Confidence threshold: {self.confidence_threshold}")
            
            frame_count = 0
            fps_start_time = time.time()
            
            while self.is_running:
                # Read frame
                ret, frame = self.camera.read()
                if not ret:
                    logger.warning("Failed to read frame from camera")
                    continue
                
                # Process frame
                processed_frame = self.process_frame(frame)
                
                # Calculate and display FPS
                frame_count += 1
                if frame_count % 30 == 0:
                    fps = 30 / (time.time() - fps_start_time)
                    logger.info(f"Processing at {fps:.1f} FPS | Total detections: {self.total_detections}")
                    fps_start_time = time.time()
                
                # Show video if requested
                if show_video:
                    cv2.imshow('Jetson Security System', processed_frame)
                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        break
                
                # Small delay to prevent overwhelming the system
                time.sleep(0.1)
                
        except KeyboardInterrupt:
            logger.info("Monitoring stopped by user")
        except Exception as e:
            logger.error(f"Error in monitoring: {e}")
        finally:
            self.stop_monitoring()
    
    def stop_monitoring(self):
        """Stop the security monitoring system"""
        self.is_running = False
        
        if self.camera:
            self.camera.release()
        
        cv2.destroyAllWindows()
        
        logger.info("Security monitoring stopped")
        logger.info(f"Session statistics:")
        logger.info(f"  Total detections: {self.total_detections}")
        logger.info(f"  Authorized: {self.authorized_count}")
        logger.info(f"  Unauthorized: {self.unauthorized_count}")

def main():
    parser = argparse.ArgumentParser(description='Jetson Nano Security System')
    parser.add_argument('--server', required=True, help='Main security system URL (e.g., http://192.168.1.100:8080)')
    parser.add_argument('--camera', type=int, default=0, help='Camera index (default: 0)')
    parser.add_argument('--confidence', type=float, default=0.5, help='Detection confidence threshold (default: 0.5)')
    parser.add_argument('--show-video', action='store_true', help='Show video output (for debugging)')
    parser.add_argument('--cooldown', type=int, default=3, help='Seconds between detections (default: 3)')
    
    args = parser.parse_args()
    
    # Create security system
    security_system = JetsonSecuritySystem(
        server_url=args.server,
        confidence_threshold=args.confidence
    )
    
    security_system.detection_cooldown = args.cooldown
    
    try:
        # Start monitoring
        security_system.start_monitoring(
            camera_index=args.camera,
            show_video=args.show_video
        )
    except Exception as e:
        logger.error(f"Failed to start security system: {e}")
        return 1
    
    return 0

if __name__ == "__main__":
    exit(main())