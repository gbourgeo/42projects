# Dockerfile to compile C projects
# Usage:
# docker build . -t gbo/make
# docker run --rm -v "$(pwd):/src" -t gbo/make

FROM	debian

# Install toolchain
RUN		apt-get update; \
		DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends gcc make libc6-dev; \
		dpkg -L binutils | grep -v  "^/usr/bin\|^/usr/lib" | while read f; do test -f $f && rm $f; done; \
		dpkg -L gcc-6    | grep -v  "^/usr/bin\|^/usr/lib" | while read f; do test -f $f && rm $f; done; \
		apt-get autoremove -y; apt-get clean; rm /var/lib/apt/lists/* -r; rm -rf /usr/share/man/*

# Builder user
RUN		apt-get update; \
		DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends adduser; \
		adduser builder --disabled-password --gecos ""; \
		echo "builder ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers; \
		sed -i "s|^#force_color_prompt=.*|force_color_prompt=yes|" /home/builder/.bashrc; \
		apt-get purge -y adduser passwd; \
		apt-get autoremove -y; apt-get clean; rm /var/lib/apt/lists/* -r; rm -rf /usr/share/man/*

RUN		echo 'export TERM=xterm' >> /home/builder/.bashrc

USER	builder

ENTRYPOINT	["/run.sh"]

COPY		run.sh /
