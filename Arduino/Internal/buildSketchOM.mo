within Arduino.Internal;
encapsulated function buildSketchOM
  extends Modelica.Icons.Function;

  import Arduino;
  import Modelica;
  input String sketch = "Blink.ino";
  input String cmake = "cmake" "Command to run CMake";
  input String generator = "Visual Studio 17 2022" "CMake generator to build the Sketch" annotation(choices(choice="Visual Studio 14 2015", choice="Visual Studio 15 2017", choice="Visual Studio 16 2019", choice="Visual Studio 17 2022"));
  input String platform = "x64" annotation(choices(choice="Win32", choice="x64"));
  output Boolean success;

protected
  String path = Modelica.Utilities.Files.loadResource("modelica://Arduino/");
  String cppFile = path + "Resources/Source/Arduino/Sketch.cpp";
  String shFile = path + "buildSketch.sh";

algorithm

  // remove the .cpp file
  remove(cppFile);

  // write the C++ file
  writeFile(cppFile, "#include \"Sketch.h\"
  
#include \"Arduino.h\"
#include \"SoftSerial.h\"

SoftSerial Serial;

// include your sketch here
#include \"" + sketch + "\"");

  // remove the build script
  remove(shFile);

  // write the build script
  writeFile(shFile, "#!/bin/bash\n" +
    "CMAKE=\"" + cmake + "\"\n" +
    "BUILD=\"" + path + "Resources/Source/Arduino/build_arduino\"\n" +
    "\n" +
    "$CMAKE -S \"" + path + "Resources/Source/Arduino\" -B $BUILD -DCMAKE_BUILD_TYPE=Release\n" +
    "if [ $? -ne 0 ]; then exit $?; fi\n" +
    "\n" +
    "$CMAKE --build $BUILD\n" +
    "if [ $? -ne 0 ]; then exit $?; fi\n" +
    "chmod +x $BUILD/*\n");  // 添加 chmod 命令确保可执行
  system("chmod +x " + shFile);  // 设置脚本文件权限

  // call the build script
  success := system(shFile + " > buildSketch.log 2>&1") == 0;

end buildSketchOM;
