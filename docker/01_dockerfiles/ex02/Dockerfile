# Download an app.
# Add or modify the Dockerfile in it to :
#
# FROM ft-rails:latest
# EXPOSE 3000
# CMD ["rails", "s", "-b", "0.0.0.0", "-p" ,"3000"]
#
# Then:
# docker build -t ft-rails .
# cd app
# docker build -t myapp -f Dockerfile .
# docker run -it -p 3000:3000 myapp
#

FROM	ruby

RUN 	apt-get update -y && apt-get install -y \
		nodejs \
		&& gem install rails \
		&& gem install bundler

ONBUILD	COPY . /opt/app
ONBUILD	WORKDIR /opt/app

ONBUILD	RUN bundle install
ONBUILD	RUN rake db:migrate
ONBUILD	RUN rake db:seed
