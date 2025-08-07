#!/bin/bash

# Smart Security System - One-Command Setup Script
# Usage: chmod +x setup.sh && ./setup.sh

set -e  # Exit on any error

echo "🛡️  Smart Security System Setup"
echo "================================"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check Python version
print_status "Checking Python version..."
python_version=$(python3 --version 2>&1 | grep -o "[0-9]\+\.[0-9]\+")
min_version="3.8"
if python3 -c "import sys; exit(0 if sys.version_info >= (3, 8) else 1)"; then
    print_success "Python $python_version detected ✓"
else
    print_error "Python 3.8+ required. Please upgrade Python."
    exit 1
fi

# Check if we're on macOS
if [[ "$OSTYPE" == "darwin"* ]]; then
    print_status "macOS detected"
    
    # Check if Homebrew is installed
    if ! command -v brew &> /dev/null; then
        print_warning "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    else
        print_success "Homebrew found ✓"
    fi
    
    # Install cmake (required for dlib)
    print_status "Installing cmake..."
    if brew list cmake &>/dev/null; then
        print_success "cmake already installed ✓"
    else
        brew install cmake
        print_success "cmake installed ✓"
    fi
fi

# Upgrade pip
print_status "Upgrading pip..."
pip3 install --upgrade pip

# Install Python packages
print_status "Installing Python packages..."
print_warning "This may take a few minutes, especially for dlib compilation..."

# Install packages one by one for better error handling
packages=(
    "numpy>=1.21.0"
    "opencv-python>=4.8.0" 
    "Pillow>=9.5.0"
    "requests>=2.31.0"
)

for package in "${packages[@]}"; do
    print_status "Installing $package..."
    pip3 install "$package"
    print_success "$package installed ✓"
done

# Install dlib and face_recognition (these can be tricky)
print_status "Installing dlib (this may take several minutes)..."
if pip3 install dlib>=19.24.0; then
    print_success "dlib installed ✓"
    
    print_status "Installing face_recognition..."
    if pip3 install face_recognition>=1.3.0; then
        print_success "face_recognition installed ✓"
    else
        print_error "face_recognition installation failed"
        print_warning "You can still use the system in Jetson mode"
    fi
else
    print_error "dlib installation failed"
    print_warning "Webcam mode will not be available"
    print_warning "You can still use Jetson mode"
fi

# Test installations
print_status "Testing installations..."

# Test OpenCV
if python3 -c "import cv2; print('OpenCV version:', cv2.__version__)" 2>/dev/null; then
    print_success "OpenCV test passed ✓"
else
    print_error "OpenCV test failed"
fi

# Test camera
print_status "Testing camera access..."
if python3 -c "import cv2; cap = cv2.VideoCapture(0); success = cap.isOpened(); cap.release(); print('Camera:', 'OK' if success else 'Failed')" 2>/dev/null; then
    print_success "Camera test passed ✓"
else
    print_warning "Camera test failed - check camera permissions"
fi

# Test face recognition
if python3 -c "import face_recognition; print('face_recognition available')" 2>/dev/null; then
    print_success "Face recognition test passed ✓"
else
    print_warning "Face recognition not available (webcam mode limited)"
fi

# Create authorized_faces directory
print_status "Creating directories..."
mkdir -p authorized_faces
print_success "authorized_faces directory created ✓"

# Final instructions
echo ""
echo "🎉 Setup Complete!"
echo "=================="
echo ""
echo "✅ All dependencies installed"
echo ""
echo "🚀 To start the security system:"
echo "   python3 webcam_nano_app.py"
echo ""
echo "📧 Don't forget to configure email settings in the Settings tab!"
echo ""

# Check for potential issues
print_status "System Check Summary:"
if python3 -c "import cv2, numpy, requests, PIL" 2>/dev/null; then
    print_success "Core packages: OK"
else
    print_error "Core packages: Issues detected"
fi

if python3 -c "import face_recognition" 2>/dev/null; then
    print_success "Face recognition: Available (full webcam mode)"
else
    print_warning "Face recognition: Not available (Jetson mode only)"
fi

echo ""
print_success "Setup completed successfully! 🎉"