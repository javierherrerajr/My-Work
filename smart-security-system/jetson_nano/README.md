# Jetson Nano Security System Setup

This guide will help you set up the Jetson Nano portion of the Smart Security System for edge AI person detection.

## 🎯 Overview

The Jetson Nano runs AI-powered person detection and sends alerts to your main computer. This creates a professional security camera system with:
- **Real-time person detection** using YOLOv5
- **Edge AI processing** (all detection happens on the Jetson)
- **Wireless alerts** sent to your main computer
- **24/7 operation** without tying up your main computer

## 📋 What You Need

### Hardware Requirements:
- **Jetson Nano Developer Kit** (4GB recommended)
- **MicroSD card** (32GB+ Class 10)
- **USB Camera or CSI Camera** (compatible with Jetson)
- **Power supply** (5V 4A barrel jack recommended)
- **Network connection** (WiFi or Ethernet)
- **Optional**: Case, fan for cooling

### Network Requirements:
- **Same network** as your main computer
- **Know your main computer's IP address** (where alerts are sent)

## 🚀 Quick Start

```bash
# 1. Copy files to Jetson Nano
scp -r jetson_nano/ jetson@<JETSON_IP>:~/

# 2. SSH into Jetson
ssh jetson@<JETSON_IP>

# 3. Install dependencies
cd jetson_nano
pip3 install -r requirements.txt

# 4. Run the security system
python3 jetson_security.py --server http://<MAIN_COMPUTER_IP>:8080
```

## 📱 Step-by-Step Setup

### Step 1: Prepare Jetson Nano

#### Flash Jetson OS (if new device):
1. **Download JetPack** from NVIDIA Developer website
2. **Flash to microSD** using Balena Etcher or NVIDIA SDK Manager
3. **Boot Jetson** and complete initial setup
4. **Enable SSH** for remote access:
   ```bash
   sudo systemctl enable ssh
   sudo systemctl start ssh
   ```

#### Update System:
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install python3-pip python3-dev build-essential -y
```

### Step 2: Install Dependencies

#### Copy Project Files:
```bash
# From your main computer, copy the jetson_nano folder
scp -r jetson_nano/ jetson@<JETSON_IP>:~/
```

#### Install Python Packages:
```bash
# SSH into Jetson
ssh jetson@<JETSON_IP>

# Navigate to project folder
cd jetson_security

# Install packages (this may take 15-30 minutes)
pip3 install -r requirements.txt
```

**Note**: Installation may take a while due to PyTorch compilation. Be patient!

#### Alternative Installation (if pip fails):
```bash
# Install system packages instead
sudo apt install python3-opencv python3-numpy python3-scipy python3-matplotlib

# Install PyTorch for Jetson
wget https://nvidia.box.com/shared/static/fjtbno0vpo676a25cgvuqc1wty0fkkg6.whl -O torch-1.10.0-cp36-cp36m-linux_aarch64.whl
pip3 install torch-1.10.0-cp36-cp36m-linux_aarch64.whl

# Install remaining packages
pip3 install ultralytics requests PyYAML tqdm psutil
```

### Step 3: Connect Camera

#### USB Camera:
```bash
# Test if camera is detected
ls /dev/video*
# Should show /dev/video0 (or similar)

# Test camera capture
python3 -c "import cv2; cap = cv2.VideoCapture(0); print('Camera OK' if cap.isOpened() else 'Camera Failed')"
```

#### CSI Camera (Raspberry Pi Camera):
```bash
# Enable CSI camera
sudo systemctl restart nvargus-daemon

# Test CSI camera
nvgstcapture-1.0
```

### Step 4: Configure Network

#### Find Your Main Computer's IP:
```bash
# On your main computer (Mac/PC), find IP address:
# macOS:
ifconfig | grep inet

# Windows:
ipconfig

# Linux:
ip addr show
```

#### Test Network Connection:
```bash
# From Jetson, test connection to main computer
ping <MAIN_COMPUTER_IP>

# Test if main computer is listening on port 8080
curl -X POST http://<MAIN_COMPUTER_IP>:8080 -H "Content-Type: application/json" -d '{"test": "connection"}'
```

### Step 5: Run the Security System

#### Basic Usage:
```bash
# Replace <MAIN_COMPUTER_IP> with your computer's actual IP
python3 jetson_security.py --server http://192.168.1.100:8080
```

#### With Custom Options:
```bash
# Show video output (for debugging)
python3 jetson_security.py --server http://192.168.1.100:8080 --show-video

# Use different camera
python3 jetson_security.py --server http://192.168.1.100:8080 --camera 1

# Adjust detection sensitivity
python3 jetson_security.py --server http://192.168.1.100:8080 --confidence 0.7

# Change detection cooldown
python3 jetson_security.py --server http://192.168.1.100:8080 --cooldown 5
```

#### All Available Options:
| Option | Description | Default |
|--------|-------------|---------|
| `--server` | Main computer URL (required) | None |
| `--camera` | Camera index (0, 1, 2...) | 0 |
| `--confidence` | Detection confidence (0.0-1.0) | 0.5 |
| `--show-video` | Show video window for debugging | False |
| `--cooldown` | Seconds between detections | 3 |

## ⚙️ Advanced Configuration

### Performance Optimization:

#### Enable Maximum Performance:
```bash
# Set maximum performance mode
sudo nvpmodel -m 0
sudo jetson_clocks
```

#### Monitor Temperature:
```bash
# Watch temperature (should stay under 80°C)
watch -n 1 cat /sys/class/thermal/thermal_zone*/temp
```

#### Add Cooling (Recommended):
- **Install fan** on heatsink for continuous operation
- **Ensure good airflow** around the device

### Auto-Start on Boot:

#### Create Systemd Service:
```bash
# Create service file
sudo nano /etc/systemd/system/jetson-security.service
```

#### Service File Content:
```ini
[Unit]
Description=Jetson Security System
After=network.target

[Service]
Type=simple
User=jetson
WorkingDirectory=/home/jetson/jetson_security
ExecStart=/usr/bin/python3 jetson_security.py --server http://192.168.1.100:8080
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
```

#### Enable Auto-Start:
```bash
# Enable and start service
sudo systemctl enable jetson-security.service
sudo systemctl start jetson-security.service

# Check status
sudo systemctl status jetson-security.service

# View logs
sudo journalctl -u jetson-security.service -f
```

## 🛠️ Troubleshooting

### Common Issues:

#### "Could not open camera"
```bash
# Check camera connections
ls /dev/video*

# Try different camera indices
python3 jetson_security.py --server http://192.168.1.100:8080 --camera 1

# For CSI camera, restart daemon
sudo systemctl restart nvargus-daemon
```

#### "Connection refused" to main computer
```bash
# Verify main computer IP
ping <MAIN_COMPUTER_IP>

# Check if main computer security system is running
curl http://<MAIN_COMPUTER_IP>:8080

# Check firewall on main computer
# Make sure port 8080 is open
```

#### "PyTorch installation failed"
```bash
# Use pre-built wheel for Jetson
wget https://nvidia.box.com/shared/static/fjtbno0vpo676a25cgvuqc1wty0fkkg6.whl -O torch-jetson.whl
pip3 install torch-jetson.whl

# Or install via conda
conda install pytorch torchvision -c pytorch
```

#### "Out of memory" during installation
```bash
# Add swap space
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

# Install packages one by one
pip3 install torch
pip3 install torchvision
pip3 install ultralytics
```

#### High temperature / thermal throttling
```bash
# Check temperature
cat /sys/class/thermal/thermal_zone*/temp

# Solutions:
# 1. Add fan cooling
# 2. Improve case ventilation
# 3. Reduce processing load:
python3 jetson_security.py --server http://192.168.1.100:8080 --cooldown 10
```

### Performance Issues:

#### Low FPS / Slow Processing:
```bash
# Reduce camera resolution in code (edit jetson_security.py):
# self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, 320)   # Lower resolution
# self.camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
# self.camera.set(cv2.CAP_PROP_FPS, 10)            # Lower FPS

# Use nano model instead of small
# In code, change: 'yolov5s' to 'yolov5n'
```

#### Network Latency:
```bash
# Increase detection cooldown to reduce network traffic
python3 jetson_security.py --server http://192.168.1.100:8080 --cooldown 10
```

## 📊 Monitoring and Logs

### View Real-time Logs:
```bash
# If running manually
python3 jetson_security.py --server http://192.168.1.100:8080

# If running as service
sudo journalctl -u jetson-security.service -f
```

### Check System Stats:
```bash
# GPU usage
sudo tegrastats

# CPU/Memory usage  
htop

# Temperature
cat /sys/class/thermal/thermal_zone*/temp
```

### Debug Mode:
```bash
# Run with video output for debugging
python3 jetson_security.py --server http://192.168.1.100:8080 --show-video

# This will show detection boxes on people
# Press 'q' to quit
```

## 🔧 Customization

### Adjust Detection Sensitivity:
```bash
# More sensitive (detects more, may have false positives)
python3 jetson_security.py --server http://192.168.1.100:8080 --confidence 0.3

# Less sensitive (fewer false positives, may miss some people)
python3 jetson_security.py --server http://192.168.1.100:8080 --confidence 0.8
```

### Change Detection Logic:
Edit `jetson_security.py` to customize the `classify_person()` function:
```python
def classify_person(self, detection):
    # Customize this logic based on your needs:
    # - Time-based rules (business hours vs after hours)
    # - Location-based rules 
    # - Integration with access control systems
    # - Face recognition (if you add face_recognition to Jetson)
    
    confidence = detection['confidence']
    current_hour = datetime.now().hour
    
    # Example: High confidence during business hours = authorized
    if 8 <= current_hour <= 18 and confidence > 0.8:
        return "authorized"
    else:
        return "unauthorized"
```

## 📞 Getting Help

### System Information:
```bash
# Get Jetson info for support
cat /etc/nv_tegra_release
python3 --version
pip3 list | grep -E "(torch|opencv|ultralytics)"
```

### Log Collection:
```bash
# Collect logs for troubleshooting
sudo journalctl -u jetson-security.service > jetson-security.log
dmesg > system.log

# Check for errors
grep -i error jetson-security.log
```

### Useful Commands:
```bash
# Restart security service
sudo systemctl restart jetson-security.service

# Check network connectivity
ping google.com
ping <MAIN_COMPUTER_IP>

# Test camera manually
python3 -c "import cv2; cap = cv2.VideoCapture(0); ret, frame = cap.read(); print('Camera working' if ret else 'Camera failed')"
```

## 🎉 Success Indicators

Your Jetson security system is working correctly when you see:

✅ **Console Output:**
```
✓ YOLOv5 model loaded successfully on cuda
✓ Camera opened with backend 1200
✓ Camera initialized successfully
Processing at 15.2 FPS | Total detections: 5
Alert sent successfully: unauthorized (0.87)
```

✅ **Main Computer Receives:**
- Detection logs appear in GUI
- Email notifications sent
- No connection errors

✅ **System Monitoring:**
- Temperature stays under 80°C
- Consistent FPS processing
- No memory errors

---

**🛡️ Your Jetson Nano security system is now ready for 24/7 monitoring!**

For issues or questions, check the troubleshooting section above or contact support with your system information and logs.