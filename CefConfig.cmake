#
# The link for downloading the CEF binary sdk 
#
set(CEF_SDK_VERSION "cef_binary_89.0.18+gb36241d+chromium-89.0.4389.114")

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Generally, there is NO NEED to modify the following config
#
# Download CEF binary package
#
if(OS_WINDOWS)
  set(CEF_SDK_PLATFORM "windows32")
elseif (OS_LINUX)
  set(CEF_SDK_PLATFORM "linux64")
elseif(OS_MACOS)
  set(CEF_SDK_PLATFORM "macosx64")
else()
  message(FATAL_ERROR "Unsupported plaftorm")
endif()

# set cef sdk package name
set(CEF_SDK_WORKSPACE       "${CMAKE_CURRENT_SOURCE_DIR}/dep")

set(CEF_SDK_PACKAGE_NAME    "${CEF_SDK_VERSION}_${CEF_SDK_PLATFORM}.tar.bz2")
set(CEF_SDK_DOWNLOAD_URL    "https://cef-builds.spotifycdn.com/${CEF_SDK_PACKAGE_NAME}")
set(CEF_SDK_LOCAL_PACKAGE   "${CEF_SDK_WORKSPACE}/${CEF_SDK_PACKAGE_NAME}")

set (CEF_SDK_EXTRACTED_DIR  "${CEF_SDK_WORKSPACE}/${CEF_SDK_VERSION}_${CEF_SDK_PLATFORM}")

message(STATUS "CEF_SDK_DOWNLOAD_URL: ${CEF_SDK_DOWNLOAD_URL}")
message(STATUS "CEF_SDK_LOCAL_PACKAGE: ${CEF_SDK_LOCAL_PACKAGE}")

# Scan extracted sdk dir
file(GLOB CEF_SDK_DIR "${CEF_SDK_EXTRACTED_DIR}")

# Extract CEF binary package
if (NOT EXISTS ${CEF_SDK_DIR})
  message(STATUS "CEF SDK dir does not exist, extracting new one....")

  # if no cef local package then download it
  if(NOT EXISTS "${CEF_SDK_LOCAL_PACKAGE}")
    message(STATUS "CEF SDK package not found, start downloading....")
    file(DOWNLOAD 
      "${CEF_SDK_DOWNLOAD_URL}"   # URL 
      "${CEF_SDK_LOCAL_PACKAGE}"  # Local Path
      SHOW_PROGRESS 
      TLS_VERIFY ON)
  endif()

  # Extract
  file(ARCHIVE_EXTRACT
    INPUT "${CEF_SDK_LOCAL_PACKAGE}"
    DESTINATION "${CEF_SDK_WORKSPACE}"
  )

  # Capture the dir name
  file(GLOB CEF_SDK_DIR "${CEF_SDK_EXTRACTED_DIR}")
endif()

# output
message(STATUS "CEF SDK dir: ${CEF_SDK_DIR}")
