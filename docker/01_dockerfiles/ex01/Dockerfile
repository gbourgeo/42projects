# docker build -t 01 .
# docker run -it --rm -p=9987:9987/udp -p=10011:10011 -p=30033:30033 01

FROM debian

#     Packages
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install bzip2 -y
RUN apt-get install curl -y

#    Install TS3
RUN useradd user
RUN curl http://dl.4players.de/ts/releases/3.3.1/teamspeak3-server_linux_amd64-3.3.1.tar.bz2 > TS3.tar.bz2
RUN tar -xvf TS3.tar.bz2
COPY ./script.sh /script.sh
RUN chmod +x /script.sh
RUN /script.sh 
WORKDIR teamspeak3-server_linux_amd64

#    Ports
EXPOSE 9987/udp
EXPOSE 10011
EXPOSE 30033

ENTRYPOINT sh ts3server_minimal_runscript.sh inifile=server.ini

