Part IV - Bonus: Different Object Detection Model (ResNet-18)

Authors: Javier and Padma 
Date: May 2nd 2025

---

🚀 Objective:
Use a different AI model (ResNet-18) for image classification on the Jetson Nano using the existing `jetson-inference` Docker container.

---

🔧 Setup and Run Instructions:

1. Clone the jetson-inference repository (if not already cloned):
```bash
git clone --recursive https://github.com/dusty-nv/jetson-inference
cd jetson-inference
```

2. Run the provided docker container:
```bash
docker/run.sh
```
- This uses the official `dusty-nv/jetson-inference` container, which has CUDA, TensorRT, and pre-trained models like ResNet-18 installed.
- No additional Dockerfile was needed for this part.

3. Inside the container:
Navigate to the binaries:
```bash
cd /jetson-inference/build/aarch64/bin
```

4. Run image classification using ResNet-18 on a sample image:
```bash
imagenet-console data/images/airplane_0.jpg output/airplane_0.jpg
```
- This command uses the ResNet-18 model to classify `airplane_0.jpg` and saves the result to `output/airplane_0.jpg`.

5. Outputs:
- Console will display the predicted label and confidence percentage (e.g., "airliner, 98% confidence").
- The output classified image will be saved in `/jetson-inference/build/aarch64/bin/output/airplane_0.jpg` inside the container.
- If volumes are mounted correctly, it can also be accessed on the host.
