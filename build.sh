#!/usr/bin/bash

#进入目标文件夹
cd ./src/proto
cd ./protogen
rm -rf *
cd ../

#用protobuf生成文件
protoc legacy.proto --cpp_out=./protogen/ --proto_path=./
srpc_generator protobuf ./legacy.proto ./protogen/
cd ./protogen

#删除例子文件
rm client.pb_skeleton.cc server.pb_skeleton.cc

#回到当前文件夹
cd ../../../

make