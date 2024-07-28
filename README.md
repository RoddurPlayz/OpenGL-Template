# OpenGL-Template

//------------------------------// What is OpenGL-Template? //------------------------------//

It is an OpenGL Template for C++.



//------------------------------// What its purpose? //------------------------------//

This OpenGL Template was made to make game developers lives a bit easier by already seting up the building for them. That way they can easily jump right in and start coding making the games they want using OpenGL.



//------------------------------// What its purpose? //------------------------------//

This template includes:
1) ENet (Networking)
2) Glad/Glew (Both are an extension of OpenGL. It's upto the developer's preference on which one to use.)
3) GLFW (Windowing)
4) GLM (Math library for OpenGL)
5) ImGUI (UI)
6) Miniaudio (Audio)
7) stb_image (Image)
8) stb_truetype (Font)



//------------------------------// Will it get updated? //------------------------------//

Yes. I'll still try to update this template and add small improvements (If there is any need of new improvements).



//------------------------------// How to use it? //------------------------------//

I'm going to refer the root directory of this template d as "root"

Step 1: Open up your desired IDE/Code Editor in the root directory.
Step 2: Run the root CMakeLists.txt file by using your desired IDE/Code Editor or you can use the terminal by navigating to the root of this termplate and running these commands:
```
mkdir build
cd build
cmake ..
```
Step 3: Compile the template for testing by using your desired IDE/Code Editor or by using a terminal (Continuing from Step 2):
```
cd ..
cmake --build build
```
Step 4: Run the executable for testing by using your desired IDE/Code Editor or by navigating to the root/build/Main and running the OpenGL-Executable executable.
Step 5: Customize the root/Main directory however you wish and rename the project in root/Main/CMakeLists.txt to whatever you wish. You can also change the root/Main directory's name if you like but then in the root/CMakeLists.txt, you will have to change the add_subdirectory command at line 37 to whatever you named the root/Main directory.

NOTE:
I have also setup some flags. These are:
1) Build Type (If your project is Debug, Relase, Release with Debug Info or Min Size Release)
2) Build Architecture (If your project is for x64 or x86 Architecture)
3) Is Production (If your project is on production or not.)

IS_PRODUCTION will change the value of the RESOURCE_PATH macro I setup in the root/Main/CMakeLists.txt file. You can change it to where ever you want your resource path to be. While trying to mention a file in your C++ files, make sure you write RESOURCE_PATH "The File you want to mention". This will tell C++ to go search in the resources folder either relative to the root/Main/CMakeLists.txt file or the executable. When IS_PRODUCTION is ON it will set RESOURCE_PATH macro to point the the resources folder directory relative to the root/Main/CMakeLists.txt and when OFF it will be relative to the executable. So make use when your project is going to be on production, your resources folder is in the same directory as your executable. Finally, if there are weird errors in CMakeLists.txt files, your project files or your configuration in CMake is unable to get modified, it's best to remove the build folder and and rebuild the project
