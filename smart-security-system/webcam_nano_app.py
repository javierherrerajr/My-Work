import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext, filedialog, simpledialog
import threading
import time
import json
import requests
from datetime import datetime, timedelta
import cv2
from PIL import Image, ImageTk
from http.server import HTTPServer, BaseHTTPRequestHandler
import socketserver
import queue
import base64
import io
import os
import numpy as np
from collections import deque
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.image import MIMEImage
from email import encoders

# Try to import face_recognition, install if not available
try:
    import face_recognition
    FACE_RECOGNITION_AVAILABLE = True
    print("✓ face_recognition loaded successfully")
except ImportError as e:
    FACE_RECOGNITION_AVAILABLE = False
    print(f"✗ face_recognition not available: {e}")
    print("Install with: pip3 install face_recognition")

class UnifiedSecurityApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Smart Security System - Unified")
        self.root.geometry("1400x900")
        
        # Queue for thread-safe GUI updates
        self.message_queue = queue.Queue()
        
        # Server for receiving Jetson Nano signals
        self.server = None
        self.server_thread = None
        
        # Mode selection
        self.current_mode = tk.StringVar(value="jetson")  # "jetson" or "webcam"
        
        # Video capture variables (for webcam mode)
        self.video_cap = None
        self.video_thread = None
        self.is_streaming = False
        self.current_frame = None
        
        # Face recognition variables (for webcam mode)
        self.known_face_encodings = []
        self.known_face_names = []
        self.authorized_faces_dir = "authorized_faces"
        
        # Detection settings
        self.detection_enabled = False
        self.last_detection_time = 0
        self.detection_cooldown = 3  # seconds
        
        # Local video capture system
        self.video_buffer = deque(maxlen=150)  # 10 seconds at 15fps
        self.buffer_seconds = 10
        self.clip_duration = 20
        self.recording_fps = 15
        
        # Create authorized faces directory
        if not os.path.exists(self.authorized_faces_dir):
            os.makedirs(self.authorized_faces_dir)
        
        # Load known faces if face recognition is available
        if FACE_RECOGNITION_AVAILABLE:
            self.load_known_faces()
        
        # Create GUI
        self.create_gui()
        
        # Start server for Jetson Nano mode
        self.start_server()
        
        # Start message processing
        self.process_messages()
        
        # Handle window close
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
    
    def on_closing(self):
        """Handle application closing"""
        try:
            # Stop webcam if running
            if self.is_streaming:
                self.stop_webcam()
            
            # Stop server if running
            if self.server:
                self.server.shutdown()
                self.server.socket.close()
                
            self.root.destroy()
        except Exception as e:
            print(f"Error during cleanup: {e}")
            self.root.destroy()
    
    def load_known_faces(self):
        """Load known authorized faces from the authorized_faces directory"""
        if not FACE_RECOGNITION_AVAILABLE:
            return
            
        self.known_face_encodings = []
        self.known_face_names = []
        
        if not os.path.exists(self.authorized_faces_dir):
            return
            
        for filename in os.listdir(self.authorized_faces_dir):
            if filename.lower().endswith(('.png', '.jpg', '.jpeg')):
                path = os.path.join(self.authorized_faces_dir, filename)
                name = os.path.splitext(filename)[0].split('_')[0]  # Get name before timestamp
                
                try:
                    # Load image and get face encoding
                    image = face_recognition.load_image_file(path)
                    encodings = face_recognition.face_encodings(image)
                    
                    if encodings:
                        self.known_face_encodings.append(encodings[0])
                        self.known_face_names.append(name)
                        print(f"Loaded authorized face: {name}")
                    else:
                        print(f"No face found in {filename}")
                        
                except Exception as e:
                    print(f"Error loading {filename}: {e}")
        
        print(f"Loaded {len(self.known_face_encodings)} authorized faces")
    
    def create_gui(self):
        """Create the main GUI interface"""
        # Mode selection at the top
        mode_frame = ttk.Frame(self.root)
        mode_frame.pack(pady=10)
        
        ttk.Label(mode_frame, text="Operation Mode:", font=("Arial", 12, "bold")).pack(side=tk.LEFT, padx=5)
        
        jetson_radio = ttk.Radiobutton(mode_frame, text="Jetson Nano Mode", 
                                      variable=self.current_mode, value="jetson",
                                      command=self.switch_mode)
        jetson_radio.pack(side=tk.LEFT, padx=10)
        
        webcam_radio = ttk.Radiobutton(mode_frame, text="Webcam Test Mode", 
                                      variable=self.current_mode, value="webcam",
                                      command=self.switch_mode)
        webcam_radio.pack(side=tk.LEFT, padx=10)
        
        if not FACE_RECOGNITION_AVAILABLE:
            webcam_radio.config(state="disabled")
            ttk.Label(mode_frame, text="(Install face_recognition for webcam mode)", 
                     foreground="red").pack(side=tk.LEFT, padx=10)
        
        # Create notebook for tabs
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Live Stream Tab
        self.stream_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.stream_frame, text="Live Stream")
        self.create_stream_tab()
        
        # Face Management Tab (for webcam mode)
        if FACE_RECOGNITION_AVAILABLE:
            self.faces_frame = ttk.Frame(self.notebook)
            self.notebook.add(self.faces_frame, text="Manage Faces")
            self.create_faces_tab()
        
        # Detection Logs Tab
        self.logs_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.logs_frame, text="Detection Logs")
        self.create_logs_tab()
        
        # Settings Tab
        self.settings_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.settings_frame, text="Settings")
        self.create_settings_tab()
        
        # Status Bar
        self.status_var = tk.StringVar()
        self.status_var.set("Ready - Select operation mode and start")
        status_bar = ttk.Label(self.root, textvariable=self.status_var, relief=tk.SUNKEN)
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)
        
        # Initialize mode
        self.switch_mode()
    
    def create_stream_tab(self):
        """Create live stream interface"""
        # Mode-specific instructions
        self.mode_instructions = ttk.Label(self.stream_frame, text="", font=("Arial", 10))
        self.mode_instructions.pack(pady=5)
        
        # Controls frame
        controls_frame = ttk.Frame(self.stream_frame)
        controls_frame.pack(pady=10)
        
        # Stream control button (changes based on mode)
        self.stream_btn = ttk.Button(controls_frame, text="Start Stream", 
                                   command=self.toggle_stream)
        self.stream_btn.pack(side=tk.LEFT, padx=5)
        
        # Detection toggle (for webcam mode)
        self.detection_btn = ttk.Button(controls_frame, text="Enable Detection", 
                                      command=self.toggle_detection)
        self.detection_btn.pack(side=tk.LEFT, padx=5)
        
        # Capture button (for webcam mode)
        self.capture_btn = ttk.Button(controls_frame, text="Capture for Training", 
                                    command=self.capture_for_training)
        self.capture_btn.pack(side=tk.LEFT, padx=5)
        
        # Video display area
        self.video_label = ttk.Label(self.stream_frame, text="Video Stream", 
                                   background="black", foreground="white")
        self.video_label.pack(pady=20, padx=20, fill=tk.BOTH, expand=True)
        
        # Detection status indicator
        status_frame = ttk.Frame(self.stream_frame)
        status_frame.pack(pady=10)
        
        self.detection_status = ttk.Label(status_frame, text="No Detection", 
                                        background="gray", foreground="white")
        self.detection_status.pack(side=tk.LEFT, padx=20)
        
        # Test detection button (for Jetson mode)
        self.test_btn = ttk.Button(status_frame, text="Test Detection", 
                                 command=self.test_detection)
        self.test_btn.pack(side=tk.LEFT, padx=10)
    
    def create_faces_tab(self):
        """Create face management interface (webcam mode only)"""
        if not FACE_RECOGNITION_AVAILABLE:
            return
            
        # Instructions
        instructions = ttk.Label(self.faces_frame, 
                                text="Manage Authorized Faces for Webcam Mode\n" +
                                     "Add photos of authorized people to train the system")
        instructions.pack(pady=10)
        
        # Face management controls
        face_controls = ttk.Frame(self.faces_frame)
        face_controls.pack(pady=10)
        
        ttk.Button(face_controls, text="Add Face from File", 
                  command=self.add_authorized_face).pack(side=tk.LEFT, padx=5)
        ttk.Button(face_controls, text="Remove Selected Face", 
                  command=self.remove_authorized_face).pack(side=tk.LEFT, padx=5)
        ttk.Button(face_controls, text="Reload All Faces", 
                  command=self.reload_faces).pack(side=tk.LEFT, padx=5)
        
        # Current faces list
        faces_label = ttk.Label(self.faces_frame, text="Authorized Faces:")
        faces_label.pack(pady=(20, 5))
        
        self.faces_listbox = tk.Listbox(self.faces_frame, height=8)
        self.faces_listbox.pack(pady=5, padx=20, fill=tk.X)
        
        # Update faces list
        self.update_faces_list()
        
        # Quick setup instructions
        setup_text = """
Quick Setup for Webcam Testing:
1. Switch to 'Webcam Test Mode' above
2. Click 'Start Webcam' to activate your webcam
3. Position yourself in camera view and click 'Capture for Training'
4. Enter your name when prompted (you'll be 'authorized')
5. Have your friend do the same (they'll be 'unauthorized' by comparison)
6. Click 'Enable Detection' to start real-time face recognition
7. Test by having both of you appear in front of the camera
        """
        
        setup_label = ttk.Label(self.faces_frame, text=setup_text, justify=tk.LEFT,
                               background="lightyellow", relief=tk.RAISED)
        setup_label.pack(pady=20, padx=20, fill=tk.X)
    
    def create_logs_tab(self):
        """Create detection logs interface"""
        # Logs display
        logs_label = ttk.Label(self.logs_frame, text="Detection Events Log")
        logs_label.pack(pady=5)
        
        # Logs text area with scrollbar
        self.logs_text = scrolledtext.ScrolledText(self.logs_frame, height=20, width=80)
        self.logs_text.pack(pady=10, padx=10, fill=tk.BOTH, expand=True)
        
        # Logs controls
        logs_controls = ttk.Frame(self.logs_frame)
        logs_controls.pack(pady=5)
        
        ttk.Button(logs_controls, text="Refresh Logs", 
                  command=self.refresh_logs).pack(side=tk.LEFT, padx=5)
        ttk.Button(logs_controls, text="Clear Logs", 
                  command=self.clear_logs).pack(side=tk.LEFT, padx=5)
        ttk.Button(logs_controls, text="Export Logs", 
                  command=self.export_logs).pack(side=tk.LEFT, padx=5)
        
        # Add welcome message
        welcome_msg = f"[{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] Unified security system started\n"
        self.logs_text.insert(tk.END, welcome_msg)
    
    def create_settings_tab(self):
        """Create settings interface"""
        # Server settings (Jetson mode)
        server_frame = ttk.LabelFrame(self.settings_frame, text="Jetson Nano Connection Settings")
        server_frame.pack(pady=10, padx=10, fill=tk.X)
        
        ttk.Label(server_frame, text="Listen Port (for receiving detection signals):").pack(anchor=tk.W, padx=5, pady=2)
        self.port_var = tk.StringVar(value="8080")
        ttk.Entry(server_frame, textvariable=self.port_var, width=10).pack(anchor=tk.W, padx=5, pady=2)
        
        ttk.Label(server_frame, text="Jetson Nano Video Stream URL:").pack(anchor=tk.W, padx=5, pady=2)
        self.jetson_stream_url_var = tk.StringVar(value="http://JETSON_IP:8081/stream")
        jetson_url_entry = ttk.Entry(server_frame, textvariable=self.jetson_stream_url_var, width=50)
        jetson_url_entry.pack(anchor=tk.W, padx=5, pady=2)
        
        # Button to open stream in browser
        stream_controls = ttk.Frame(server_frame)
        stream_controls.pack(anchor=tk.W, padx=5, pady=5)
        
        ttk.Button(stream_controls, text="Open Stream in Browser", 
                  command=self.open_jetson_stream).pack(side=tk.LEFT, padx=5)
        ttk.Button(stream_controls, text="Test Connection", 
                  command=self.test_jetson_connection).pack(side=tk.LEFT, padx=5)
        
        # Instructions
        instructions_text = """
Instructions for Jetson setup:
1. Set up your Jetson Nano with the security system
2. Replace 'JETSON_IP' with your Jetson's actual IP address
3. Example: http://192.168.1.150:8081/stream
4. Use 'Test Connection' to verify the stream is accessible
        """
        instructions_label = ttk.Label(server_frame, text=instructions_text, 
                                     foreground="gray", justify=tk.LEFT)
        instructions_label.pack(anchor=tk.W, padx=5, pady=5)
        
        # Camera settings (Webcam mode)
        camera_frame = ttk.LabelFrame(self.settings_frame, text="Webcam Settings")
        camera_frame.pack(pady=10, padx=10, fill=tk.X)
        
        ttk.Label(camera_frame, text="Camera Index:").pack(anchor=tk.W, padx=5, pady=2)
        self.camera_index_var = tk.StringVar(value="0")
        ttk.Entry(camera_frame, textvariable=self.camera_index_var, width=10).pack(anchor=tk.W, padx=5, pady=2)
        
        ttk.Label(camera_frame, text="Detection Cooldown (seconds):").pack(anchor=tk.W, padx=5, pady=2)
        self.cooldown_var = tk.StringVar(value="3")
        ttk.Entry(camera_frame, textvariable=self.cooldown_var, width=10).pack(anchor=tk.W, padx=5, pady=2)
        
        # Test webcam button
        ttk.Button(camera_frame, text="Test Webcam", command=self.test_webcam).pack(anchor=tk.W, padx=5, pady=5)
        
        # Email settings
        email_frame = ttk.LabelFrame(self.settings_frame, text="Email Notification Settings")
        email_frame.pack(pady=10, padx=10, fill=tk.X)
        
        # Instructions
        instructions = ttk.Label(email_frame, text="Configure where to send security alerts:", 
                                font=("Arial", 10, "bold"))
        instructions.pack(anchor=tk.W, padx=5, pady=5)
        
        # Only show recipient email (user configurable)
        ttk.Label(email_frame, text="Send alerts to this email:").pack(anchor=tk.W, padx=5, pady=2)
        self.recipient_email_var = tk.StringVar(value="")
        ttk.Entry(email_frame, textvariable=self.recipient_email_var, width=40).pack(anchor=tk.W, padx=5, pady=2)
        
        # Test email button
        test_frame = ttk.Frame(email_frame)
        test_frame.pack(anchor=tk.W, padx=5, pady=10)
        
        ttk.Button(test_frame, text="Send Test Alert", command=self.test_email).pack(side=tk.LEFT)
        
        # Status label for test results
        self.email_status_var = tk.StringVar(value="Enter your email above and click 'Send Test Alert'")
        self.email_status_label = ttk.Label(test_frame, textvariable=self.email_status_var, 
                                           foreground="gray")
        self.email_status_label.pack(side=tk.LEFT, padx=10)
        
        # Hidden sender credentials (hardcoded - user can't see/change)
        self.smtp_server_var = tk.StringVar(value="smtp.gmail.com")  # Change to your SMTP
        self.smtp_port_var = tk.StringVar(value="587")
        self.sender_email_var = tk.StringVar(value="jherr116@ucr.edu")  # ← CHANGE THIS
        self.sender_password_var = tk.StringVar(value="vjwl aedz srfy tfmx")        # ← CHANGE THIS
        
        # Email help
        help_text = ttk.Label(email_frame, 
                             text="💡 You'll receive instant email alerts when unauthorized people are detected",
                             foreground="blue")
        help_text.pack(anchor=tk.W, padx=5, pady=5)
        
        # Notification settings
        notif_frame = ttk.LabelFrame(self.settings_frame, text="Notification Settings")
        notif_frame.pack(pady=10, padx=10, fill=tk.X)
        
        self.notify_authorized = tk.BooleanVar(value=False)
        ttk.Checkbutton(notif_frame, text="Notify on Authorized Person", 
                       variable=self.notify_authorized).pack(anchor=tk.W, padx=5, pady=2)
        
        self.notify_unauthorized = tk.BooleanVar(value=True)
        ttk.Checkbutton(notif_frame, text="Notify on Unauthorized Person", 
                       variable=self.notify_unauthorized).pack(anchor=tk.W, padx=5, pady=2)
        
        # Save settings button
        ttk.Button(self.settings_frame, text="Save Settings", 
                  command=self.save_settings).pack(pady=20)
        
        # Add cleanup settings
        cleanup_frame = ttk.LabelFrame(self.settings_frame, text="Evidence File Management")
        cleanup_frame.pack(pady=10, padx=10, fill=tk.X)
        
        ttk.Label(cleanup_frame, text="Automatically delete evidence files after:").pack(anchor=tk.W, padx=5, pady=2)
        self.cleanup_days_var = tk.StringVar(value="7")
        cleanup_entry_frame = ttk.Frame(cleanup_frame)
        cleanup_entry_frame.pack(anchor=tk.W, padx=5, pady=2)
        ttk.Entry(cleanup_entry_frame, textvariable=self.cleanup_days_var, width=5).pack(side=tk.LEFT)
        ttk.Label(cleanup_entry_frame, text="days").pack(side=tk.LEFT, padx=5)
        
        cleanup_controls = ttk.Frame(cleanup_frame)
        cleanup_controls.pack(anchor=tk.W, padx=5, pady=5)
        
        ttk.Button(cleanup_controls, text="Clean Up Now", command=self.cleanup_old_evidence).pack(side=tk.LEFT, padx=5)
        ttk.Button(cleanup_controls, text="View Evidence Folder", command=self.open_evidence_folder).pack(side=tk.LEFT, padx=5)
        
        # Evidence folder info
        info_text = "Evidence files (photos, videos, reports) are automatically created when unauthorized people are detected."
        ttk.Label(cleanup_frame, text=info_text, foreground="gray", wraplength=400).pack(anchor=tk.W, padx=5, pady=5)
    
    def cleanup_old_evidence(self):
        """Clean up old evidence files"""
        try:
            days_to_keep = int(self.cleanup_days_var.get())
            cutoff_date = datetime.now() - timedelta(days=days_to_keep)
            
            # Directories to clean
            directories = ["security_clips", "security_photos", "security_logs"]
            total_removed = 0
            
            for directory in directories:
                if os.path.exists(directory):
                    removed_count = 0
                    for filename in os.listdir(directory):
                        file_path = os.path.join(directory, filename)
                        if os.path.isfile(file_path):
                            file_time = datetime.fromtimestamp(os.path.getctime(file_path))
                            
                            if file_time < cutoff_date:
                                os.remove(file_path)
                                removed_count += 1
                    
                    total_removed += removed_count
                    print(f"🧹 Cleaned {removed_count} files from {directory}")
            
            messagebox.showinfo("Cleanup Complete", 
                f"Removed {total_removed} old evidence files.\n\n" +
                f"Files older than {days_to_keep} days were deleted.")
            
        except ValueError:
            messagebox.showerror("Error", "Please enter a valid number of days.")
        except Exception as e:
            messagebox.showerror("Cleanup Error", f"Error during cleanup: {e}")
    
    def open_evidence_folder(self):
        """Open the evidence folder in file explorer"""
        try:
            import subprocess
            import platform
            
            # Create base evidence directory if it doesn't exist
            base_dir = os.path.abspath(".")
            
            system = platform.system()
            if system == "Darwin":  # macOS
                subprocess.run(["open", base_dir])
            elif system == "Windows":
                subprocess.run(["explorer", base_dir])
            else:  # Linux
                subprocess.run(["xdg-open", base_dir])
                
        except Exception as e:
            messagebox.showerror("Error", f"Could not open folder: {e}")
    
    def test_email(self):
        """Test email configuration"""
        try:
            self.send_email_notification(
                "Test Alert", 
                "This is a test email from your security system.", 
                "test"
            )
            messagebox.showinfo("Email Test", "Test email sent successfully!")
        except Exception as e:
            messagebox.showerror("Email Test Failed", f"Failed to send test email:\n{str(e)}")
    
    def test_webcam(self):
        """Test webcam functionality"""
        try:
            camera_index = int(self.camera_index_var.get())
            
            # Try to open camera
            cap = cv2.VideoCapture(camera_index)
            
            if not cap.isOpened():
                messagebox.showerror("Webcam Test", f"Could not open camera with index {camera_index}")
                return
            
            # Try to read a frame
            ret, frame = cap.read()
            if not ret:
                messagebox.showerror("Webcam Test", "Could not read frame from camera")
                cap.release()
                return
            
            cap.release()
            messagebox.showinfo("Webcam Test", f"Camera {camera_index} is working properly!")
            
        except ValueError:
            messagebox.showerror("Error", "Invalid camera index. Please enter a number.")
        except Exception as e:
            messagebox.showerror("Webcam Test", f"Error testing webcam: {e}")
    
    def switch_mode(self):
        """Switch between Jetson and Webcam modes"""
        mode = self.current_mode.get()
        
        if mode == "jetson":
            # Jetson Nano mode
            self.mode_instructions.config(text="JETSON NANO MODE: Receiving detection signals from Jetson Nano device")
            self.stream_btn.config(text="Show Stream URL")
            self.detection_btn.pack_forget()
            self.capture_btn.pack_forget()
            self.test_btn.pack(side=tk.LEFT, padx=10)
            self.video_label.config(text="Waiting for Jetson Nano stream...\nConnect to: http://JETSON_IP:8081/stream")
            self.status_var.set("Jetson mode - Server listening on port 8080")
            
        elif mode == "webcam":
            # Webcam mode
            if FACE_RECOGNITION_AVAILABLE:
                self.mode_instructions.config(text="WEBCAM TEST MODE: Using local webcam for face recognition testing")
                self.stream_btn.config(text="Start Webcam")
                self.detection_btn.pack(side=tk.LEFT, padx=5)
                self.capture_btn.pack(side=tk.LEFT, padx=5)
                self.test_btn.pack_forget()
                self.video_label.config(text="Webcam feed will appear here")
                self.status_var.set("Webcam mode - Click 'Start Webcam' to begin")
            else:
                messagebox.showerror("Error", "face_recognition library not installed.\nInstall with: pip install face_recognition")
                self.current_mode.set("jetson")
                return
    
    def toggle_stream(self):
        """Toggle stream based on current mode"""
        mode = self.current_mode.get()
        
        if mode == "jetson":
            # Open Jetson stream in browser
            self.open_jetson_stream()
        
        elif mode == "webcam":
            # Toggle webcam
            if not self.is_streaming:
                self.start_webcam()
            else:
                self.stop_webcam()
    
    def open_jetson_stream(self):
        """Open Jetson stream URL in browser"""
        import webbrowser
        try:
            stream_url = self.jetson_stream_url_var.get()
            if "JETSON_IP" in stream_url:
                messagebox.showwarning("Configuration Needed", 
                    "Please update the Jetson stream URL in Settings.\n\n" +
                    "Replace 'JETSON_IP' with your Jetson Nano's actual IP address.\n" +
                    "Example: http://192.168.1.150:8081/stream")
                return
            
            webbrowser.open(stream_url)
            messagebox.showinfo("Stream Opened", 
                f"Opening Jetson video stream in your browser:\n{stream_url}")
        except Exception as e:
            messagebox.showerror("Error", f"Could not open stream: {e}")
    
    def test_jetson_connection(self):
        """Test connection to Jetson Nano stream"""
        try:
            import urllib.request
            
            stream_url = self.jetson_stream_url_var.get()
            if "JETSON_IP" in stream_url:
                messagebox.showwarning("Configuration Needed", 
                    "Please replace 'JETSON_IP' with your Jetson's actual IP address first.")
                return
            
            # Test if the URL is reachable
            req = urllib.request.Request(stream_url, method='HEAD')
            with urllib.request.urlopen(req, timeout=5) as response:
                if response.getcode() == 200:
                    messagebox.showinfo("Connection Test", 
                        f"✅ Successfully connected to Jetson stream!\n{stream_url}")
                else:
                    messagebox.showwarning("Connection Test", 
                        f"⚠️ Got response code {response.getcode()}\n{stream_url}")
                        
        except urllib.error.URLError as e:
            messagebox.showerror("Connection Test", 
                f"❌ Could not connect to Jetson stream:\n{e}\n\n" +
                "Make sure:\n" +
                "• Jetson Nano is powered on\n" +
                "• Jetson security system is running\n" +
                "• IP address is correct\n" +
                "• Both devices are on same network")
        except Exception as e:
            messagebox.showerror("Connection Test", 
                f"❌ Connection test failed:\n{e}")
    
    def start_webcam(self):
        """Start webcam stream"""
        try:
            camera_index = int(self.camera_index_var.get())
            
            # Release any existing capture
            if self.video_cap:
                self.video_cap.release()
                time.sleep(0.5)  # Give time for camera to release
            
            # Try different backends for better compatibility
            backends = [cv2.CAP_AVFOUNDATION, cv2.CAP_ANY]  # macOS specific backend first
            
            self.video_cap = None
            for backend in backends:
                try:
                    print(f"Trying camera {camera_index} with backend {backend}")
                    self.video_cap = cv2.VideoCapture(camera_index, backend)
                    
                    if self.video_cap.isOpened():
                        # Test if we can actually read a frame
                        ret, test_frame = self.video_cap.read()
                        if ret and test_frame is not None:
                            print(f"Successfully opened camera {camera_index} with backend {backend}")
                            break
                        else:
                            self.video_cap.release()
                            self.video_cap = None
                    else:
                        if self.video_cap:
                            self.video_cap.release()
                        self.video_cap = None
                except Exception as e:
                    print(f"Backend {backend} failed: {e}")
                    if self.video_cap:
                        self.video_cap.release()
                    self.video_cap = None
            
            if not self.video_cap or not self.video_cap.isOpened():
                messagebox.showerror("Error", f"Could not open camera {camera_index}. Try different camera indices (0, 1, 2) in Settings.")
                return
            
            # Set camera properties with error handling
            try:
                self.video_cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
                self.video_cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
                self.video_cap.set(cv2.CAP_PROP_FPS, 30)
                self.video_cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Reduce buffer for lower latency
            except Exception as e:
                print(f"Warning: Could not set camera properties: {e}")
            
            self.is_streaming = True
            self.stream_btn.config(text="Stop Webcam")
            
            # Start video thread
            self.video_thread = threading.Thread(target=self.webcam_worker, daemon=True)
            self.video_thread.start()
            
            self.status_var.set("Webcam started - Ready for detection")
            print("Webcam thread started successfully")
            
        except ValueError:
            messagebox.showerror("Error", "Invalid camera index. Please enter a number.")
        except Exception as e:
            print(f"Webcam start error: {e}")
            messagebox.showerror("Error", f"Could not start webcam: {e}")
    
    def stop_webcam(self):
        """Stop webcam stream"""
        self.is_streaming = False
        self.detection_enabled = False
        
        # Wait a moment for thread to stop
        time.sleep(0.1)
        
        if self.video_cap:
            self.video_cap.release()
            self.video_cap = None
        
        self.stream_btn.config(text="Start Webcam")
        self.detection_btn.config(text="Enable Detection")
        self.detection_status.config(text="No Detection", background="gray")
        self.status_var.set("Webcam stopped")
        
        # Clear video display
        self.video_label.config(image="", text="Webcam feed will appear here")
        if hasattr(self.video_label, 'image'):
            delattr(self.video_label, 'image')
    
    def toggle_detection(self):
        """Toggle face detection on/off"""
        if self.current_mode.get() != "webcam":
            return
            
        if not self.is_streaming:
            messagebox.showwarning("Warning", "Please start webcam first")
            return
        
        if len(self.known_face_encodings) == 0:
            messagebox.showwarning("Warning", "No authorized faces loaded. Please add at least one authorized face.")
            return
        
        self.detection_enabled = not self.detection_enabled
        
        if self.detection_enabled:
            self.detection_btn.config(text="Disable Detection")
            self.detection_status.config(text="Detection: ON", background="green")
            self.status_var.set("Face detection enabled")
        else:
            self.detection_btn.config(text="Enable Detection")
            self.detection_status.config(text="Detection: OFF", background="gray")
            self.status_var.set("Face detection disabled")
    
    def webcam_worker(self):
        """Webcam processing worker thread"""
        while self.is_streaming and self.video_cap:
            try:
                ret, frame = self.video_cap.read()
                if not ret:
                    print("Failed to read frame from webcam")
                    break
                
                # Store current frame for capture
                self.current_frame = frame.copy()
                
                # Add frame to buffer for video recording
                timestamp = time.time()
                self.video_buffer.append({
                    'frame': frame.copy(),
                    'timestamp': timestamp
                })
                
                # Process frame for face detection if enabled
                if self.detection_enabled and FACE_RECOGNITION_AVAILABLE:
                    frame = self.process_frame_for_detection(frame)
                
                # Convert frame to display format
                frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                image = Image.fromarray(frame_rgb)
                
                # Resize to fit display
                image = image.resize((640, 480), Image.Resampling.LANCZOS)
                photo = ImageTk.PhotoImage(image)
                
                # Update GUI in main thread
                self.message_queue.put(('video_frame', photo))
                
                # Control frame rate
                time.sleep(0.033)  # ~30 FPS
                
            except Exception as e:
                print(f"Webcam error: {e}")
                break
        
        print("Webcam worker thread ended")
    
    def process_frame_for_detection(self, frame):
        """Process frame for face detection and recognition"""
        if not FACE_RECOGNITION_AVAILABLE:
            return frame
            
        # Only process every few frames for performance
        current_time = time.time()
        if current_time - self.last_detection_time < float(self.cooldown_var.get()):
            return frame
        
        # Resize frame for faster processing
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_small_frame = cv2.cvtColor(small_frame, cv2.COLOR_BGR2RGB)
        
        # Find faces in frame
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
        
        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            # Scale back up face locations since the frame was scaled to 1/4 size
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4
            
            # Compare with known faces
            matches = face_recognition.compare_faces(self.known_face_encodings, face_encoding)
            name = "Unknown"
            confidence = 0
            
            if True in matches:
                # Calculate distances to find best match
                face_distances = face_recognition.face_distance(self.known_face_encodings, face_encoding)
                best_match_index = np.argmin(face_distances)
                if matches[best_match_index]:
                    name = self.known_face_names[best_match_index]
                    confidence = 1 - face_distances[best_match_index]
            
            # Determine if authorized
            is_authorized = name != "Unknown"
            
            # Draw rectangle and label
            color = (0, 255, 0) if is_authorized else (0, 0, 255)
            cv2.rectangle(frame, (left, top), (right, bottom), color, 2)
            
            label = f"{name} ({'Authorized' if is_authorized else 'Unauthorized'})"
            cv2.putText(frame, label, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
            
            # Log detection
            if current_time - self.last_detection_time >= float(self.cooldown_var.get()):
                self.log_detection(name, is_authorized, confidence)
                self.last_detection_time = current_time
        
        return frame
    
    def log_detection(self, person_name, is_authorized, confidence):
        """Log a detection event with video and photo capture"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        person_type = "authorized" if is_authorized else "unauthorized"
        
        detection_data = {
            'person_type': person_type,
            'person_name': person_name,
            'confidence': confidence,
            'timestamp': timestamp,
            'source': 'webcam'
        }
        
        # If unauthorized detection, capture video and photo evidence
        video_path = None
        photo_path = None
        summary_path = None
        
        if not is_authorized and self.current_frame is not None:
            print("🎥 Capturing evidence for unauthorized detection...")
            
            # Create evidence directories only when needed
            clips_dir = "security_clips"
            logs_dir = "security_logs"
            photos_dir = "security_photos"
            
            os.makedirs(clips_dir, exist_ok=True)
            os.makedirs(logs_dir, exist_ok=True)
            os.makedirs(photos_dir, exist_ok=True)
            
            # Capture detection photo
            photo_path = self.capture_detection_photo(detection_data, photos_dir)
            
            # Capture video clip
            video_path = self.capture_detection_video(detection_data, clips_dir)
            
            # Create summary report
            summary_path = self.create_detection_summary(detection_data, logs_dir, photo_path, video_path)
            
            # Update detection data with file paths
            detection_data.update({
                'evidence': {
                    'photo_path': photo_path,
                    'video_path': video_path,
                    'summary_path': summary_path
                }
            })
        
        self.message_queue.put(('detection', detection_data))
    
    def capture_detection_photo(self, detection_data, photos_dir):
        """Capture and save detection photo with overlay"""
        try:
            timestamp = datetime.now()
            filename = f"detection_{timestamp.strftime('%Y%m%d_%H%M%S')}_{int(detection_data.get('confidence', 0)*100)}.jpg"
            photo_path = os.path.join(photos_dir, filename)
            
            # Create photo with detection overlay
            overlay_frame = self.add_detection_overlay(self.current_frame, detection_data, timestamp)
            
            # Save photo
            cv2.imwrite(photo_path, overlay_frame)
            
            # Get file size
            file_size = os.path.getsize(photo_path)
            print(f"📸 Detection photo saved: {filename} ({file_size/1024:.1f}KB)")
            
            return photo_path
            
        except Exception as e:
            print(f"❌ Error capturing detection photo: {e}")
            return None
    
    def capture_detection_video(self, detection_data, clips_dir):
        """Capture video clip from buffer and post-detection frames"""
        try:
            timestamp = datetime.now()
            filename = f"detection_{timestamp.strftime('%Y%m%d_%H%M%S')}_{int(detection_data.get('confidence', 0)*100)}.mp4"
            video_path = os.path.join(clips_dir, filename)
            
            if not self.current_frame.any():
                return None
            
            # Get frame dimensions
            height, width = self.current_frame.shape[:2]
            
            # Create video writer
            fourcc = cv2.VideoWriter_fourcc(*'mp4v')
            video_writer = cv2.VideoWriter(video_path, fourcc, self.recording_fps, (width, height))
            
            print(f"📹 Creating detection video: {filename}")
            
            # Write buffered frames (pre-detection)
            frames_written = 0
            for frame_data in self.video_buffer:
                video_writer.write(frame_data['frame'])
                frames_written += 1
            
            # Add highlighted detection frame
            highlighted_frame = self.add_detection_overlay(self.current_frame, detection_data, timestamp)
            video_writer.write(highlighted_frame)
            frames_written += 1
            
            # Continue with highlighted frame for a few more seconds
            post_detection_frames = (self.clip_duration - self.buffer_seconds) * self.recording_fps
            for _ in range(int(post_detection_frames)):
                video_writer.write(highlighted_frame)
                frames_written += 1
            
            video_writer.release()
            
            # Get file size
            file_size = os.path.getsize(video_path)
            print(f"✅ Video clip created: {frames_written} frames, {file_size/1024/1024:.1f}MB")
            
            # Update detection data with video info
            detection_data.update({
                'video_clip': {
                    'filename': filename,
                    'path': video_path,
                    'duration_seconds': frames_written / self.recording_fps,
                    'file_size_mb': file_size / 1024 / 1024,
                    'frame_count': frames_written
                }
            })
            
            return video_path
            
        except Exception as e:
            print(f"❌ Error creating video clip: {e}")
            return None
    
    def add_detection_overlay(self, frame, detection_data, timestamp):
        """Add visual overlay to detection frame"""
        if frame is None:
            return None
            
        overlay_frame = frame.copy()
        
        # Add red border for unauthorized detection
        border_color = (0, 0, 255)  # Red for unauthorized
        border_thickness = 8
        cv2.rectangle(overlay_frame, (0, 0), 
                     (frame.shape[1]-1, frame.shape[0]-1), 
                     border_color, border_thickness)
        
        # Add detection information
        person_name = detection_data.get('person_name', 'Unknown')
        confidence = detection_data.get('confidence', 0)
        timestamp_str = timestamp.strftime("%Y-%m-%d %H:%M:%S")
        
        # Main detection text
        main_text = f"UNAUTHORIZED: {person_name}"
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 1.0
        text_thickness = 2
        
        # Get text size for background
        (text_width, text_height), _ = cv2.getTextSize(main_text, font, font_scale, text_thickness)
        
        # Add semi-transparent background
        overlay = overlay_frame.copy()
        cv2.rectangle(overlay, (10, 10), (text_width + 30, text_height + 80), (0, 0, 0), -1)
        cv2.addWeighted(overlay, 0.7, overlay_frame, 0.3, 0, overlay_frame)
        
        # Add main text
        cv2.putText(overlay_frame, main_text, (20, 35), 
                   font, font_scale, (0, 0, 255), text_thickness)
        
        # Add confidence score
        confidence_text = f"Confidence: {confidence:.2f}"
        cv2.putText(overlay_frame, confidence_text, (20, 60), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # Add timestamp
        cv2.putText(overlay_frame, timestamp_str, (20, 80), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # Add timestamp at bottom of frame
        bottom_text = f"Security Alert - {timestamp_str}"
        cv2.putText(overlay_frame, bottom_text, 
                   (20, frame.shape[0] - 20), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
        
        return overlay_frame
    
    def create_detection_summary(self, detection_data, logs_dir, photo_path, video_path):
        """Create a text summary file for the detection"""
        try:
            timestamp = datetime.now()
            summary_filename = f"detection_summary_{timestamp.strftime('%Y%m%d_%H%M%S')}.txt"
            summary_path = os.path.join(logs_dir, summary_filename)
            
            with open(summary_path, 'w') as f:
                f.write("SECURITY SYSTEM DETECTION REPORT\n")
                f.write("=" * 40 + "\n\n")
                f.write(f"Detection Time: {timestamp.strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write(f"Person Type: {detection_data.get('person_type', 'Unknown')}\n")
                f.write(f"Person Name: {detection_data.get('person_name', 'Unknown')}\n")
                f.write(f"Confidence: {detection_data.get('confidence', 0):.2f}\n")
                f.write(f"Source: {detection_data.get('source', 'Unknown')}\n")
                f.write(f"Device: unified_security_system\n")
                
                f.write(f"\nEvidence Files:\n")
                if photo_path:
                    f.write(f"  Detection Photo: {os.path.basename(photo_path)}\n")
                if video_path:
                    f.write(f"  Video Clip: {os.path.basename(video_path)}\n")
                
                if 'video_clip' in detection_data:
                    video_info = detection_data['video_clip']
                    f.write(f"\nVideo Clip Information:\n")
                    f.write(f"  Duration: {video_info.get('duration_seconds', 0):.1f} seconds\n")
                    f.write(f"  File Size: {video_info.get('file_size_mb', 0):.1f} MB\n")
                    f.write(f"  Frame Count: {video_info.get('frame_count', 0)}\n")
                
                f.write(f"\nSystem Configuration:\n")
                f.write(f"  Video Buffer: {self.buffer_seconds} seconds\n")
                f.write(f"  Total Clip Duration: {self.clip_duration} seconds\n")
                f.write(f"  Recording FPS: {self.recording_fps}\n")
                f.write(f"  Detection Cooldown: {self.detection_cooldown} seconds\n")
                
            return summary_path
            
        except Exception as e:
            print(f"Error creating summary: {e}")
            return None
    
    def capture_for_training(self):
        """Capture current frame for training"""
        if self.current_mode.get() != "webcam" or not self.is_streaming or self.current_frame is None:
            messagebox.showwarning("Warning", "Please start webcam first")
            return
        
        # Ask for person's name
        name = simpledialog.askstring("Capture Face", "Enter person's name:")
        if not name:
            return
        
        # Save the current frame
        filename = f"{name}_{int(time.time())}.jpg"
        filepath = os.path.join(self.authorized_faces_dir, filename)
        
        cv2.imwrite(filepath, self.current_frame)
        
        # Reload faces
        self.reload_faces()
        
        messagebox.showinfo("Success", f"Captured and saved face for {name}")
    
    def add_authorized_face(self):
        """Add authorized face from file"""
        filename = filedialog.askopenfilename(
            title="Select face image",
            filetypes=[("Image files", "*.jpg *.jpeg *.png")]
        )
        
        if filename:
            # Ask for person's name
            name = simpledialog.askstring("Person Name", "Enter person's name:")
            if name:
                # Copy file to authorized faces directory
                import shutil
                new_filename = f"{name}_{int(time.time())}.jpg"
                new_filepath = os.path.join(self.authorized_faces_dir, new_filename)
                shutil.copy2(filename, new_filepath)
                
                self.reload_faces()
                messagebox.showinfo("Success", f"Added {name} to authorized faces")
    
    def remove_authorized_face(self):
        """Remove selected authorized face"""
        if not hasattr(self, 'faces_listbox'):
            return
            
        selection = self.faces_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a face to remove")
            return
        
        face_name = self.faces_listbox.get(selection[0])
        
        # Find and remove file
        for filename in os.listdir(self.authorized_faces_dir):
            if filename.startswith(face_name):
                os.remove(os.path.join(self.authorized_faces_dir, filename))
                break
        
        self.reload_faces()
        messagebox.showinfo("Success", f"Removed {face_name}")
    
    def reload_faces(self):
        """Reload authorized faces"""
        if FACE_RECOGNITION_AVAILABLE:
            self.load_known_faces()
            self.update_faces_list()
    
    def update_faces_list(self):
        """Update the faces listbox"""
        if hasattr(self, 'faces_listbox'):
            self.faces_listbox.delete(0, tk.END)
            for name in self.known_face_names:
                self.faces_listbox.insert(tk.END, name)
    
    def test_detection(self):
        """Test detection functionality (Jetson mode)"""
        if self.current_mode.get() == "jetson":
            self.simulate_detection("unauthorized")
    
    def simulate_detection(self, person_type):
        """Simulate a detection event (for Jetson mode)"""
        data = {
            'person_type': person_type,
            'confidence': 0.95,
            'timestamp': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            'source': 'jetson'
        }
        self.message_queue.put(('detection', data))
    
    def start_server(self):
        """Start HTTP server to receive Jetson Nano signals"""
        class SignalHandler(BaseHTTPRequestHandler):
            def __init__(self, *args, app_instance=None, **kwargs):
                self.app = app_instance
                super().__init__(*args, **kwargs)
            
            def do_POST(self):
                content_length = int(self.headers['Content-Length'])
                post_data = self.rfile.read(content_length)
                
                try:
                    data = json.loads(post_data.decode('utf-8'))
                    data['source'] = 'jetson'  # Mark as Jetson source
                    self.app.message_queue.put(('detection', data))
                    
                    self.send_response(200)
                    self.send_header('Content-type', 'application/json')
                    self.end_headers()
                    self.wfile.write(json.dumps({"status": "received"}).encode())
                    
                except Exception as e:
                    self.send_response(400)
                    self.end_headers()
                    print(f"Error processing request: {e}")
            
            def log_message(self, format, *args):
                pass  # Suppress server logs
        
        def create_handler():
            def handler(*args, **kwargs):
                SignalHandler(*args, app_instance=self, **kwargs)
            return handler
        
        try:
            port = int(self.port_var.get())
            self.server = HTTPServer(('localhost', port), create_handler())
            self.server_thread = threading.Thread(target=self.server.serve_forever, daemon=True)
            self.server_thread.start()
            print(f"Server listening on http://localhost:{port}")
        except Exception as e:
            messagebox.showerror("Server Error", f"Could not start server: {e}")
    
    def process_messages(self):
        """Process messages from worker threads"""
        try:
            while True:
                message_type, data = self.message_queue.get_nowait()
                
                if message_type == 'detection':
                    self.handle_detection(data)
                elif message_type == 'video_frame':
                    self.video_label.config(image=data)
                    self.video_label.image = data  # Keep reference
                    
        except queue.Empty:
            pass
        
        # Schedule next check
        self.root.after(100, self.process_messages)
    
    def handle_detection(self, data):
        """Handle detection event from Jetson Nano or webcam"""
        timestamp = data.get('timestamp', datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
        person_type = data.get('person_type', 'unknown')
        person_name = data.get('person_name', 'Unknown Person')
        confidence = data.get('confidence', 0)
        source = data.get('source', 'unknown')
        
        # Update detection status
        if person_type == 'authorized':
            if source == 'webcam':
                self.detection_status.config(text=f"✓ {person_name} (Authorized)", background="green")
            else:
                self.detection_status.config(text="✓ Authorized Person", background="green")
        else:
            if source == 'webcam':
                self.detection_status.config(text=f"⚠ {person_name} (Unauthorized)", background="red")
            else:
                self.detection_status.config(text="⚠ Unauthorized Person", background="red")
        
        # Log the event
        source_label = "WEBCAM" if source == 'webcam' else "JETSON"
        if source == 'webcam':
            log_entry = f"[{timestamp}] [{source_label}] {person_type.title()}: {person_name} (confidence: {confidence:.2f})"
        else:
            log_entry = f"[{timestamp}] [{source_label}] {person_type.title()} person detected (confidence: {confidence:.2f})"
        
        self.logs_text.insert(tk.END, log_entry + "\n")
        self.logs_text.see(tk.END)
        
        # Store in local logs
        self.store_detection_log(timestamp, person_type, confidence, source, person_name)
        
        # Send notification
        self.send_notification(person_type, timestamp, person_name, source)
        
        # Reset status after 3 seconds
        self.root.after(3000, lambda: self.detection_status.config(
            text="No Detection" if source == 'jetson' else "Detection: ON", 
            background="gray" if source == 'jetson' else ("green" if self.detection_enabled else "gray")))
    
    def store_detection_log(self, timestamp, person_type, confidence, source, person_name="Unknown"):
        """Store detection event in local log file"""
        try:
            log_data = {
                'timestamp': timestamp,
                'person_type': person_type,
                'person_name': person_name,
                'confidence': confidence,
                'source': source,
                'device_id': 'unified_security_system'
            }
            
            # Append to local log file
            with open('detection_logs.json', 'a') as f:
                f.write(json.dumps(log_data) + '\n')
            
            print(f"Local Log: {timestamp} - {person_type} ({person_name}) from {source} ({confidence})")
            
        except Exception as e:
            print(f"Error storing log: {e}")
    
    def send_notification(self, person_type, timestamp, person_name="Unknown", source="unknown"):
        """Send email notification with photo and video attachments"""
        # Check notification settings
        if person_type == 'authorized' and not self.notify_authorized.get():
            return
        if person_type == 'unauthorized' and not self.notify_unauthorized.get():
            return
        
        try:
            if person_type == 'authorized':
                title = "Authorized Access"
                if source == 'webcam':
                    body = f"{person_name} detected via webcam at {timestamp}"
                else:
                    body = f"Authorized person detected via Jetson Nano at {timestamp}"
            else:
                title = "Security Alert"
                if source == 'webcam':
                    body = f"Unauthorized person ({person_name}) detected via webcam at {timestamp}"
                else:
                    body = f"Unauthorized person detected via Jetson Nano at {timestamp}"
            
            # Send email notification with attachments for unauthorized detections
            self.send_email_notification(title, body, person_type)
            
            # Demo mode
            print(f"Email sent: {title} - {body}")
            self.status_var.set(f"Email sent: {title}")
            
        except Exception as e:
            print(f"Error sending notification: {e}")
    
    def send_email_notification(self, subject, body, alert_type):
        """Send email notification with evidence attachments"""
        try:
            # Use hardcoded sender credentials (user can't see these)
            smtp_server = self.smtp_server_var.get()
            smtp_port = int(self.smtp_port_var.get())
            sender_email = self.sender_email_var.get()
            sender_password = self.sender_password_var.get()
            recipient_email = self.recipient_email_var.get()
            
            if not recipient_email.strip():
                raise Exception("No recipient email configured. Please set your email address in Settings.")
            
            # Validate hardcoded credentials
            if sender_email == "your-security-system@gmail.com" or sender_password == "your-app-password-here":
                raise Exception("Email system not configured properly. Please contact the system administrator.")
            
            # Create message
            msg = MIMEMultipart()
            msg['From'] = f"Smart Security System <{sender_email}>"
            msg['To'] = recipient_email
            msg['Subject'] = f"🛡️ Security Alert: {subject}"
            
            # Find latest evidence files for unauthorized detections
            photo_path = None
            video_path = None
            summary_path = None
            
            if alert_type == "unauthorized":
                # Look for the most recent evidence files
                photo_path = self.find_latest_evidence_file("security_photos", ".jpg")
                video_path = self.find_latest_evidence_file("security_clips", ".mp4")
                summary_path = self.find_latest_evidence_file("security_logs", ".txt")
            
            # Enhanced HTML email body
            if alert_type == "test":
                html_body = f"""
                <html>
                <body style="font-family: Arial, sans-serif; line-height: 1.6; color: #333;">
                    <div style="max-width: 600px; margin: 0 auto; padding: 20px; border: 1px solid #ddd; border-radius: 10px;">
                        <h2 style="color: #2196F3; text-align: center;">
                            🛡️ Smart Security System - Test Email
                        </h2>
                        <div style="background: #f0f8ff; padding: 15px; border-radius: 5px; margin: 20px 0;">
                            <p><strong>✅ Email Configuration Test</strong></p>
                            <p>{body}</p>
                        </div>
                        <hr style="border: 1px solid #eee; margin: 20px 0;">
                        <p style="font-size: 12px; color: #666; text-align: center;">
                            This is an automated test message from your Smart Security System.<br>
                            If you received this, your email notifications are working correctly!
                        </p>
                    </div>
                </body>
                </html>
                """
            else:
                # Real security alert with evidence
                evidence_section = ""
                if photo_path or video_path or summary_path:
                    evidence_section = """
                    <div style="background: #fff3cd; padding: 15px; border-radius: 5px; margin: 20px 0; border-left: 4px solid #ffc107;">
                        <p><strong>📋 Evidence Attached:</strong></p>
                        <ul>
                    """
                    if photo_path:
                        evidence_section += f"<li>📸 Detection Photo: {os.path.basename(photo_path)}</li>"
                    if video_path:
                        evidence_section += f"<li>📹 Video Clip: {os.path.basename(video_path)}</li>"
                    if summary_path:
                        evidence_section += f"<li>📄 Detailed Report: {os.path.basename(summary_path)}</li>"
                    evidence_section += """
                        </ul>
                    </div>
                    """
                
                alert_color = "#4CAF50" if alert_type == "authorized" else "#f44336"
                html_body = f"""
                <html>
                <body style="font-family: Arial, sans-serif; line-height: 1.6; color: #333;">
                    <div style="max-width: 600px; margin: 0 auto; padding: 20px; border: 1px solid #ddd; border-radius: 10px;">
                        <h2 style="color: {alert_color}; text-align: center;">
                            🛡️ SECURITY ALERT
                        </h2>
                        <div style="background: {'#e8f5e8' if alert_type == 'authorized' else '#ffebee'}; padding: 15px; border-radius: 5px; margin: 20px 0; border-left: 4px solid {alert_color};">
                            <p><strong>Alert Type:</strong> {subject}</p>
                            <p><strong>Details:</strong> {body}</p>
                            <p><strong>Time:</strong> {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}</p>
                            <p><strong>Status:</strong> <span style="color: {alert_color}; font-weight: bold;">{alert_type.upper()}</span></p>
                        </div>
                        
                        {evidence_section}
                        
                        <div style="background: #f8f9fa; padding: 10px; border-radius: 5px; margin: 20px 0;">
                            <p><strong>⚠️ Next Steps:</strong></p>
                            <ul>
                                <li>Review attached evidence carefully</li>
                                <li>Verify if this was authorized access</li>
                                <li>Contact security personnel if needed</li>
                                <li>Evidence files are stored locally and auto-deleted after 7 days</li>
                            </ul>
                        </div>
                        
                        <hr style="border: 1px solid #eee; margin: 20px 0;">
                        <p style="font-size: 12px; color: #666; text-align: center;">
                            This is an automated security alert from your Smart Security System.<br>
                            Evidence files are automatically cleaned up after 7 days for privacy.
                        </p>
                    </div>
                </body>
                </html>
                """
            
            msg.attach(MIMEText(html_body, 'html'))
            
            # Attach evidence files for unauthorized detections
            if alert_type == "unauthorized":
                # Attach detection photo
                if photo_path and os.path.exists(photo_path):
                    try:
                        with open(photo_path, "rb") as f:
                            img_data = f.read()
                        image = MIMEImage(img_data)
                        image.add_header('Content-Disposition', f'attachment; filename={os.path.basename(photo_path)}')
                        msg.attach(image)
                        print(f"📎 Photo attached: {os.path.basename(photo_path)}")
                    except Exception as e:
                        print(f"⚠️ Could not attach photo: {e}")
                
                # Attach video file
                if video_path and os.path.exists(video_path):
                    try:
                        with open(video_path, "rb") as attachment:
                            part = MIMEBase('application', 'octet-stream')
                            part.set_payload(attachment.read())
                        
                        encoders.encode_base64(part)
                        part.add_header('Content-Disposition', f'attachment; filename={os.path.basename(video_path)}')
                        msg.attach(part)
                        print(f"📎 Video attached: {os.path.basename(video_path)}")
                    except Exception as e:
                        print(f"⚠️ Could not attach video: {e}")
                
                # Attach summary report
                if summary_path and os.path.exists(summary_path):
                    try:
                        with open(summary_path, "rb") as attachment:
                            part = MIMEBase('application', 'octet-stream')
                            part.set_payload(attachment.read())
                        
                        encoders.encode_base64(part)
                        part.add_header('Content-Disposition', f'attachment; filename={os.path.basename(summary_path)}')
                        msg.attach(part)
                        print(f"📎 Report attached: {os.path.basename(summary_path)}")
                    except Exception as e:
                        print(f"⚠️ Could not attach report: {e}")
            
            # Send email
            with smtplib.SMTP(smtp_server, smtp_port) as server:
                server.starttls()
                server.login(sender_email, sender_password)
                server.send_message(msg)
            
            print(f"📧 Email notification sent successfully to {recipient_email}")
            
        except Exception as e:
            print(f"❌ Failed to send email: {e}")
            self.status_var.set(f"Email failed: {str(e)[:50]}...")
    
    def find_latest_evidence_file(self, directory, extension):
        """Find the most recent file in a directory with given extension"""
        try:
            if not os.path.exists(directory):
                return None
            
            files = [f for f in os.listdir(directory) if f.endswith(extension)]
            if not files:
                return None
            
            # Sort by modification time, most recent first
            files.sort(key=lambda x: os.path.getmtime(os.path.join(directory, x)), reverse=True)
            return os.path.join(directory, files[0])
            
        except Exception as e:
            print(f"Error finding latest evidence file: {e}")
            return None
    
    def refresh_logs(self):
        """Refresh logs from local file"""
        try:
            if os.path.exists('detection_logs.json'):
                self.logs_text.delete(1.0, tk.END)
                
                with open('detection_logs.json', 'r') as f:
                    lines = f.readlines()
                    # Show last 100 entries
                    for line in lines[-100:]:
                        try:
                            data = json.loads(line.strip())
                            source_label = data.get('source', 'unknown').upper()
                            person_name = data.get('person_name', 'Unknown')
                            log_entry = f"[{data['timestamp']}] [{source_label}] {data['person_type'].title()}: {person_name} (confidence: {data.get('confidence', 0):.2f})"
                            self.logs_text.insert(tk.END, log_entry + "\n")
                        except json.JSONDecodeError:
                            continue
                            
                messagebox.showinfo("Logs Refreshed", "Local logs refreshed successfully!")
            else:
                messagebox.showinfo("No Logs", "No log file found. Logs will be created when detections occur.")
                
        except Exception as e:
            messagebox.showerror("Error", f"Could not refresh logs: {e}")
    
    def clear_logs(self):
        """Clear logs display"""
        if messagebox.askyesno("Confirm", "Clear all logs from display?"):
            self.logs_text.delete(1.0, tk.END)
    
    def export_logs(self):
        """Export logs to file"""
        filename = filedialog.asksaveasfilename(
            defaultextension=".txt",
            filetypes=[("Text files", "*.txt"), ("All files", "*.*")]
        )
        if filename:
            try:
                with open(filename, 'w') as f:
                    f.write(self.logs_text.get(1.0, tk.END))
                messagebox.showinfo("Success", f"Logs exported to {filename}")
            except Exception as e:
                messagebox.showerror("Error", f"Could not export logs: {e}")
    
    def save_settings(self):
        """Save application settings"""
        try:
            # Update detection cooldown
            self.detection_cooldown = float(self.cooldown_var.get())
            
            # Restart server with new port if changed
            if self.server:
                self.server.shutdown()
                self.start_server()
            
            messagebox.showinfo("Settings", "Settings saved successfully!")
        except Exception as e:
            messagebox.showerror("Error", f"Could not save settings: {e}")

def main():
    # Check if required packages are installed
    required_packages = ['opencv-python', 'pillow', 'requests']
    missing_packages = []
    
    for package in required_packages:
        try:
            if package == 'opencv-python':
                import cv2
            elif package == 'pillow':
                import PIL
            elif package == 'requests':
                import requests
        except ImportError:
            missing_packages.append(package)
    
    if missing_packages:
        print("Missing required packages. Please install them with:")
        print(f"pip install {' '.join(missing_packages)}")
        
    if not FACE_RECOGNITION_AVAILABLE:
        print("\nOptional: Install face_recognition for webcam mode:")
        print("pip install face_recognition")
        print("Note: On Windows, you may need to install cmake and dlib first:")
        print("pip install cmake")
        print("pip install dlib")
    
    # Create and run the application
    root = tk.Tk()
    app = UnifiedSecurityApp(root)
    
    print("\n=== Unified Smart Security System Started ===")
    print("Features:")
    print("- Jetson Nano Mode: Receives detection signals from Jetson Nano")
    print("- Webcam Test Mode: Real-time face recognition with your webcam")
    print("- Email notifications with evidence attachments")
    print("- HTTP server listening on port 8080")
    print("==============================================")
    
    try:
        root.mainloop()
    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        # Cleanup
        if hasattr(app, 'video_cap') and app.video_cap:
            app.video_cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()