### Netcat from debian
# docker build . -t gbo/nc
###
### Connect from host to docker machine
# $> docker run -it -p [port]:[port] gbo/nc -l -p [port]
# $> nc [docker-machine ip [machine_name]] [port]
###
## ortherwise:
# $> nc -l [port]
# $> docker run -it gbo/nc [host_ip] [port]
#

FROM debian:sid-slim

RUN apt-get update && apt-get install -y netcat --no-install-recommends \
	&& rm -rf /var/lib/apt/lists/*

ENTRYPOINT [ "netcat" ]
