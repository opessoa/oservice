# oservice
Tests with drogon and jwt


First of all

```
sudo apt-get update
```

Install all the requirenments

```
sudo apt install gcc g++ cmake libjsoncpp-dev uuid-dev openssl libssl-dev zlib1g-dev nlohmann-json3-dev libsqlite3-dev
```

Clone and install oservice
```
git clone https://github.com/opessoa/oservice.git
cd oservice/
git submodule update --init --recursive
mkdir build
cd build/
cmake ..
make
.\oservice --install
.\oservice
```