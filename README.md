# OpenGL-Template

//------------------------------// What is OpenGL-Template? //------------------------------//

It is an OpenGL Template for C++.



//------------------------------// What its purpose? //------------------------------//

This OpenGL Template was made to make game developers lives a bit easier by already seting up the building for them. That way they can easily jump right in and start coding making the games they want using OpenGL.



//------------------------------// What its purpose? //------------------------------//

This template includes:
1) Assimp # (Model loading)
2) ENet (Networking)
3) Glad (An extension of OpenGL)
4) GLFW (Windowing)
5) GLM (Math library for OpenGL)
6) ImGUI (UI)
7) Miniaudio (2D Audio)
8) Nlohmann's JSON Library (For reading .json files)
9) OpenAL (3D Audio)
10) stb_image (Image)
11) stb_truetype (Font)



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
Step 5: Customize the root/Main directory however you wish and rename the project in root/CMakeLists.txt to whatever you wish. You can also change the root/Main directory's name if you like but then in the root/CMakeLists.txt, you will have to change all the PROJECT_DIRECTORY variable to whatever you named it to at line 7 to whatever you named the root/Main directory.

NOTE:
I have also setup a varable called ON_PRODUCTION

ON_PRODUCTION will change the value of the RESOURCE_PATH macro I setup in the root/CMakeLists.txt file. You can change it to where ever you want your resource path to be. While trying to mention a file in your C++ files, make sure you write RESOURCE_PATH "The File you want to mention". This will tell C++ to go search in the resources folder either relative to the root/Main/resources file or the executable. When ON_PRODUCTION is ON it will set RESOURCE_PATH macro to point to the resources folder directory relative to the executable. So make use when your project is going to be on production, your resources folder is in the same directory as your executable. Finally, if there are weird errors in CMakeLists.txt files, your project files or your configuration in CMake is unable to get modified, it's best to remove the build folder and and rebuild the entire project.
