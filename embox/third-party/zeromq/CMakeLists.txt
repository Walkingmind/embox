include(ExternalProject)
ExternalProject_Add(
   zeromq
   PREFIX ..
   DOWNLOAD_DIR ../../../download
   URL http://download.zeromq.org/zeromq-3.2.2.tar.gz
   URL_MD5 df68431d9300da84a1a5f9a2784e33de
   UPDATE_COMMAND ""
   PATCH_COMMAND
      cd $ENV{EMBOX_ROOT}/third-party/zeromq/tree
      #&& bash -c "cp -l -u -f --parents -t <SOURCE_DIR>/ `find . -not -path '*/.*' -and -type f`"
      && patch -p1 -d <SOURCE_DIR> -N --input=$ENV{EMBOX_ROOT}/third-party/zeromq/patch_zeromq.txt 
   LOG_CONFIGURE 1
   CONFIGURE_COMMAND
      <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
      ""CFLAGS=$ENV{EMBOX_DERIVED_CFLAGS}""
      ""CXXFLAGS=$ENV{EMBOX_DERIVED_CXXFLAGS}""
      ""LDFLAGS=$ENV{EMBOX_DERIVED_LDFLAGS}""
      --with-poller=select
      --enable-debug
      --host=i386-pc-none
   #	BUILD_COMMAND
   LOG_BUILD 1
)
ExternalProject_Add(
   czmq
   DEPENDS zeromq
   PREFIX ..
   DOWNLOAD_DIR ../../../download
   URL http://download.zeromq.org/czmq-1.3.2.tar.gz
   URL_MD5 513fb1f9a7030c71c7d9a3a61f9970db
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
      cd $ENV{EMBOX_ROOT}/third-party/zeromq/tree
      #&& bash -c "cp -l -u -f --parents -t <SOURCE_DIR>/ `find . -not -path '*/.*' -and -type f`"
      && patch -p1 -d <SOURCE_DIR> -N --input=$ENV{EMBOX_ROOT}/third-party/zeromq/patch_czmq.txt 
   LOG_CONFIGURE 1
   CONFIGURE_COMMAND
      <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
      ""CFLAGS=$ENV{EMBOX_DERIVED_CFLAGS}""
      ""CXXFLAGS=$ENV{EMBOX_DERIVED_CXXFLAGS}""
      ""LDFLAGS=$ENV{EMBOX_DERIVED_LDFLAGS}""
      --with-libzmq=<INSTALL_DIR>
      --host=i386-pc-none
   BUILD_COMMAND true
   INSTALL_COMMAND true
   LOG_BUILD 1
)

ExternalProject_Add(
   zmq_host
   PREFIX ../host
   DOWNLOAD_DIR ../../../download
   URL http://download.zeromq.org/zeromq-3.2.2.tar.gz
   URL_MD5 df68431d9300da84a1a5f9a2784e33de
   UPDATE_COMMAND ""
   PATCH_COMMAND
      cd $ENV{EMBOX_ROOT}/third-party/zeromq/tree
      #&& bash -c "cp -l -u -f --parents -t <SOURCE_DIR>/ `find . -not -path '*/.*' -and -type f`"
      && patch -p1 -d <SOURCE_DIR> -N --input=$ENV{EMBOX_ROOT}/third-party/zeromq/patch_zeromq.txt 
   LOG_CONFIGURE 1
   CONFIGURE_COMMAND
      <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
         --enable-static --disable-shared --enable-debug
   LOG_BUILD 1
)

project (zmq_examples)
SET (CMAKE_BUILD_TYPE "Debug")

add_executable(hwclient hwclient.cpp)
add_dependencies(hwclient zmq_host)
include_directories("${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/include")
#link_directories(${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/lib)
target_link_libraries(hwclient ${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/lib/libzmq.a)
target_link_libraries(hwclient pthread rt)

add_executable(hwserver hwserver.cpp)
add_dependencies(hwserver zmq_host)
include_directories("${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/include")
#link_directories(${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/lib)
target_link_libraries(hwserver ${PROJECT_SOURCE_DIR}/../../build/extbld/third_party/zeromq/core/host/lib/libzmq.a)
target_link_libraries(hwserver pthread rt)
