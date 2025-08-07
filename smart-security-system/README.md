# Smart Security System - Unified

This is a Smart Home Security System that is designed to be able to setup a recognized face and send an email for when there's someone unrecognized

## 🚀 Quick Start (One Command)

```bash
# Clone or download this repository
git clone https://github.com/jherr116/smart-security-system.git
cd smart-security-system

# Run one-command setup
chmod +x setup.sh
./setup.sh

# Launch the application
python3 webcam_nano_app.py

# Clean up repository
python3 cleanup.py
```

## 📋 What You Need

- **macOS, Linux, or Windows**
- **Python 3.8+**
- **Webcam** (built-in or USB)
- **Internet connection** (for email notifications)
- **Optional**: Jetson Nano if available

## 📁 Project Structure

### Main Computer (Command Center):
```
smart-security-system/
├── setup.sh                    # One-command installer (included)
├── requirements.txt            # Dependencies (included)
├── webcam_nano_app.py          # Main security system (included)
├── cleanup.py                  # Cleans all generated files (included)
├── README.md                   # This file (included)
```

### Jetson Nano (Edge Detection):
```
jetson_security/
├── requirements.txt           # Jetson dependencies (included)
├── jetson_security.py         # Jetson detection code (included)
└── README.md                  # Jetson setup instructions (included)
```

## 🎯 Complete Setup Guide

### Step 1: Main Computer Setup

1. **Download the project files**:
   ```bash
   # Option A: Git clone
   git clone https://github.com/your-username/smart-security-system.git
   cd smart-security-system
   
   # Option B: Download ZIP and extract
   # Download from GitHub → Extract → Open terminal in folder
   ```

2. **Run the setup script**:
   ```bash
   chmod +x setup.sh
   ./setup.sh
   ```
   
   This will:
   - ✅ Check Python version
   - ✅ Install cmake (macOS)
   - ✅ Install all dependencies
   - ✅ Test camera and face recognition
   - ✅ Create launcher script

3. **Launch the application**:
   ```bash
   python3 webcam_nano_app.py
   ```

4. **Cleans up any generated files**:
   ```bash
   python3 cleanup.py
   ```

### Step 2: Configure Email Notifications

1. **Go to Settings tab** in the application
2. **Enter your email**
4. **Click "Test Email"** to verify configuration

### Step 3: Train Face Recognition (Webcam Mode)

1. **Switch to "Webcam Test Mode"**
2. **Click "Start Webcam"**
3. **Position yourself in view** and click "Capture for Training"
4. **Enter your name** when prompted
5. **Add more authorized people** as needed
6. **Click "Enable Detection"** to start monitoring

### Step 4: Jetson Nano Setup 

1. **Copy jetson files to your Jetson Nano**:
   ```bash
   scp -r jetson_security/ user@jetson-ip:~/
   ```

2. **On the Jetson Nano**:
   ```bash
   cd jetson_security
   pip3 install -r requirements.txt
   python3 jetson_security.py --server http://YOUR_COMPUTER_IP:8080
   ```

## 🎯 Features

- **🎥 Webcam Face Recognition** - Real-time authorized/unauthorized detection
- **🤖 Jetson Nano Integration** - Production-grade edge AI deployment  
- **📧 Email Notifications** - Instant alerts with photo, video, and txt attachments
- **📊 Detection Logging** - Comprehensive activity logs
- **⚙️ Easy Configuration** - GUI-based settings management
- **🔄 Dual Mode Operation** - Test with webcam, deploy with Jetson

## 🛠️ Troubleshooting

### Installation Issues

**"dlib installation failed"**
```bash
# macOS
brew install cmake
pip3 install dlib

# Ubuntu/Linux
sudo apt install cmake build-essential
pip3 install dlib
```

**"face_recognition not available"**
```bash
# After installing dlib successfully
pip3 install face_recognition
```

**"Python version too old"**
```bash
# macOS - install newer Python
brew install python@3.11

# Ubuntu
sudo apt install python3.11
```

### Camera Issues

**"Could not open camera"**
- Check camera permissions (System Preferences → Privacy → Camera on macOS)
- Close other apps using camera (Zoom, Photo Booth, etc.)
- Try different camera indices (0, 1, 2) in Settings tab

**"Camera test failed"**
```bash
# Test camera manually
python3 -c "import cv2; cap = cv2.VideoCapture(0); print('Camera:', 'OK' if cap.isOpened() else 'Failed')"
```
### Network Issues (Jetson Mode)

**"Connection refused"**
- Verify main computer IP address
- Check firewall settings on main computer
- Ensure both devices on same network
- Test connection: `curl -X POST http://MAIN_COMPUTER_IP:8080`

## 📱 Usage Modes

### 🖥️ Webcam Test Mode (Development/Testing)
- **Purpose**: Test face recognition locally
- **Setup**: Configure webcam, train faces, enable detection
- **Best for**: Development, testing, single-location monitoring

### 🤖 Jetson Nano Mode (Production)
- **Purpose**: Professional deployment with edge AI
- **Setup**: Configure Jetson Nano, connect to main system
- **Best for**: Production environments, multiple cameras, remote locations

## 🔧 Advanced Configuration

### Performance Optimization
```bash
# For better face recognition accuracy
# Use good lighting, clear frontal photos
# Capture multiple angles of the same person

# For Jetson Nano optimization
# Reduce camera resolution in jetson_security.py
# Increase detection cooldown to reduce CPU usage
```

## 🆘 Support Commands

```bash
# Test all components
python3 -c "
import cv2, numpy, requests, PIL
print('✅ Core packages working')
try:
    import face_recognition
    print('✅ Face recognition available')
except:
    print('❌ Face recognition not available')
"

# Check camera
python3 -c "
import cv2
cap = cv2.VideoCapture(0)
if cap.isOpened():
    print('✅ Camera working')
    cap.release()
else:
    print('❌ Camera not accessible')
"

# Re-run setup if needed
./setup.sh

# View logs
tail -f ~/.python_history  # Python errors
```

## 📊 System Requirements

### Minimum Requirements:
- **CPU**: Dual-core 2.0GHz
- **RAM**: 4GB
- **Storage**: 2GB free space
- **Camera**: USB/Built-in webcam
- **Network**: Wi-Fi/Ethernet for notifications

### Recommended for Production:
- **CPU**: Quad-core 2.5GHz+
- **RAM**: 8GB+
- **Jetson Nano**: For edge AI processing
- **Multiple Cameras**: USB hubs for expansion

---

**🛡️ Your security system is ready! Stay safe and monitor smart!** 

For questions or issues, please check the troubleshooting section or create an issue on GitHub.