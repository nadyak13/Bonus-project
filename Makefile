src_files = src/interface/*.cpp src/model/*.cpp src/logic/*.cpp
include_files = -I include/interface -I include/model -I include/logic


all: build

main_client: $(src_files)
	g++ src/main_client.cpp $(src_files) $(include_files) -std=c++11 -o main_client -Wall -Werror

main_admin: $(src_files) 
	g++ src/main_admin.cpp $(src_files) $(include_files) -std=c++11 -o main_admin -Wall -Werror

build: main_admin main_client

admin: main_admin
	./main_admin

client: main_client
	./main_client

clean:
	rm -f main_client -f main_admin 

