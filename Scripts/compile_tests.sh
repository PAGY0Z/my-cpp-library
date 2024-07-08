mkdir Build/
cd Build/
cmake -DBUILD_TESTS=ON -DCODE_COVERAGE=ON ..
make
ctest
cd ..
gcovr -e Tests/ -e Build/
gcovr -e Tests/ -e Build/ -b
