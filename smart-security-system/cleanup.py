import os, shutil
dirs = ['authorized_faces', 'security_clips', 'security_photos', 'security_logs']
files = ['detection_logs.json']
for d in dirs:
    if os.path.exists(d):
        shutil.rmtree(d)
        print(f"Removed directory: {d}")
for f in files:
    if os.path.exists(f):
        os.remove(f)
        print(f"Removed file: {f}")
print("Cleanup complete.")