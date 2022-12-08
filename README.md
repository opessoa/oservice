# oservice
Tests with drogon and jwt



sudo apt-get update
sudo apt install gcc
sudo apt install g++
sudo apt install cmake
sudo apt install libjsoncpp-dev
sudo apt install uuid-dev
sudo apt install openssl libssl-dev
sudo apt install zlib1g-dev
sudo apt install nlohmann-json3-dev
sudo apt install libsqlite3-dev

git clone https://github.com/opessoa/oservice.git
cd oservice/
git submodule update --init --recursive

mkdir build
cd build/
cmake ..
make