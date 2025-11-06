Lab 2 - Object Recognition: Part 1.1 - Docker Container for Process Monitoring

Author: Javier Herrera Jr
Date: 5/2/25

---

✅ Build Docker Image:
docker build -t htop-monitor .

---

✅ Run Container with Volume Mounted:
mkdir -p ~/docker_volume
docker run -it --name monitor-volume -v ~/docker_volume:/data htop-monitor

---

✅ Inside the container:
1. Start htop to observe system processes:
   htop

2. In a new terminal, connect to the same container:
   docker exec -it monitor-volume bash

3. Run a background CPU-heavy process:
   bash -c "while true; do :; done" &

4. In the first terminal, observe htop and take a screenshot showing CPU usage.

5. In the second terminal, capture a snapshot of processes:
   top -b -n 1 > /data/busy_process.txt

6. Exit the container:
   exit

---

✅ After container is stopped, verify on host:
cat ~/docker_volume/busy_process.txt
