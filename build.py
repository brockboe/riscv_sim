import os

os.system("rm -rf ./build")
os.system("mkdir -p ./build")
os.chdir("build")
os.system("cmake ..")
os.system("make")