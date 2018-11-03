# docker built -t tetris .
# docker run -it tetris

FROM	debian:sid-slim

RUN		apt-get update && apt-get install -y emacs --no-install-recommends \
		&& rm -rf /var/lib/apt/lists/*

CMD [ "/usr/bin/emacs", "-f", "tetris" ]
