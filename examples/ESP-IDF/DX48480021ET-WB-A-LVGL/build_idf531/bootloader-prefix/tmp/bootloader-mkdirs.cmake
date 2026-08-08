# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/wbj/Soft/ESP-IDF_V_5.3/Espressif/frameworks/esp-idf-v5.3.1/components/bootloader/subproject"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/tmp"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/src/bootloader-stamp"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/src"
  "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/wbj/AI-Project/ESP32-S3-view/ESP32/examples/ESP-IDF/DX48480021ET-WB-A-LVGL/build_idf531/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
