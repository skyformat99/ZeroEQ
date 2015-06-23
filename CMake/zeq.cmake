
set(ZEQ_VERSION 0.1)
set(ZEQ_REPO_URL https://github.com/HBPVIS/zeq.git)
set(ZEQ_DEPENDS hbpvis REQUIRED Threads libzmq FlatBuffers Boost Servus)
set(ZEQ_OPTIONAL ON)
set(ZEQ_BOOST_COMPONENTS "unit_test_framework")
set(ZEQ_DEB_DEPENDS libboost-test-dev)

if(CI_BUILD_COMMIT)
  set(ZEQ_REPO_TAG ${CI_BUILD_COMMIT})
else()
  set(ZEQ_REPO_TAG master)
endif()
set(ZEQ_FORCE_BUILD ON)
set(ZEQ_SOURCE ${CMAKE_SOURCE_DIR})