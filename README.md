# oservice
Tests with drogon and jwt


`sudo apt-get update`

```
sudo apt install gcc g++ cmake libjsoncpp-dev uuid-dev openssl libssl-dev zlib1g-dev nlohmann-json3-dev libsqlite3-dev
```

`git clone https://github.com/opessoa/oservice.git`
`cd oservice/`
`git submodule update --init --recursive`
`mkdir build`
`cd build/`
`cmake ..`
`make`
`.\oservice --install`
`.\oservice`