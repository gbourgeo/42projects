# DOCKER
*Thinking with containers*

## 00 How to Docker
1. Create a virtual machine with docker-machine using virtualbox driver with the name Char
2. Get the ip address of Char
3. Assign the specific Char variables to the current terminal environment
4. Get from the Docker Hub the container hello-world
5. Launch container hello-world
6. Launch a container nginx from DockerHub in background. His name must be overlord, he must restart himself, and must have port 80 of the container attached to the port 5000 of Char
7. Retrieve the internal IP address of the overlord container without launching its shell and in one command
8. Launch a shell from an alpine container, ensuring that you can directly interact with the container via your terminal and that the container is deleted at the end of the execution of the shell.
9. From the shell of a debian container, make sure to install via the container's package manager, what to compile a source code in C and pusher on a repo git (making sure to update the manager of packets and basic packages present in the container). Only orders to be made in the container are requested for this exercise
10. Create a volume hatchery
11. List the docker volumes created on the machine
12. Launch a mysql container in the background. It should also be able to restart itself if an error occurs and make sure that the root password of the database is Kerrigan. You will also make sure that the database is stored in the hatchery volume, that the container directly creates a database with the name zerglings and the container will be called spawning-pool.
13. Display the environment variables of the container spawning-pool in a single command, just to be sure that you have configured your container.
14. Launch a wordpress container in the background for the lulz. The container must be named air, port 80 of the container must be bound to port 8080 of the virtual machine and must be able to use the spawning-pool container as a database service. You can try to access the air on your machine via a browser by entering the IP address of the virtual machine as a URL. Congratulations, you have just deployed a functional Wordpress site in 2 orders!
15. Launch a phpmyadmin container in the background. The container must have the name roach-warden, the port 80 of the container must be bound to the port 8081 of the virtual machine and must be able to make sure to go to explore the database contained in the container spawning-pool.
16. View the real-time logs of the spawning-pool container without executing its shell.
17. View all currently active containers on the Char virtual machine.
18. Restart the overlord container
19. Start a container named Abathur. Abathur will be a 2-slim Python container, which will have its folder / root bound to a home folder of your host, as well as port 3000 bound to port 3000 of your virtual machine. You will customize this container so that you can use the Flask microframework in its latest version. You will need to make a html page that returns a "Hello World" in \<h1\> tags, served by Flask. You will test the correct implementation of your container, by accessing via curl or web browser, the IP address of your virtual machine on port 3000. You will also list all the necessary commands in your rendering.
20. Create a local swarm where the Char virtual machine is the manager.

21. Create another virtual machine with docker-machine using the virtualbox driver and named Aiur
22. Toggle Aiur as a slave to the local swarm where Char is leader (Aiur's takeover command is not requested).
23. Create an internal network of type overlay that you will name overmind.
24. Launch a rabbitmq service that will be named orbital-command. You will need to define a user and password specific to the use of the RabbitMQ service, and these will be at your sole discretion. This service will be on the overmind network

25. List all services of the local swarm.
26. Start a 42school / engineering-bay service in 2 replicas and make the service work (refer to the doc provided in hub.docker.com). This service will be called engineering-bay and will be on the overmind network
27. Retrieve logs continuously from one of the engineering-bay service tasks
28. ... Damn, zerg are attacking orbital-command and cutting the engineering-bay service will not help ... You must send Marines to eliminate them ... Start a service 42school / marine- squad in 2 replicas, and make sure the service works (refer to the doc provided in hub.docker.com). This service will be called ... marine and will be on the overmind network
29. Display all the tasks of the marine service.
30. Update the number of marine service replicates to 20 because there are never enough Marines to annihilate Zerg. (Also remember to look at the tasks and logs of the service, you'll see, it's funny).
31. Force shutdown and remove all services on the local swarm, in one command
32. Force the shutdown and delete all the containers (all states combined), in a single command.
33. Delete all the images of containers stored on the virtual machine Char, in one command too.
34. Remove Aiur virtual machine otherwise than with rm -rf

## 01 Dockerfiles
1. From an alpine image, you will add to your container the text editor of your choice between vim or emacs, which will launch at the start of your container.
2. From a debian image, you will add the appropriate sources to create a server TeamSpeak, server that will start at startup of your container. It is considered valid if at least one user can log on and discuss normally (no risky configuration), so create your Dockerfile with the appropriate options. You must ensure that the sources are recovered from the build, they must not be present in the repository
3. You will create your first Dockerfile Rails application container. This Dockerfile will be a bit special because it will be generic and will have to be called in another Dockerfile, which should look a little like this:
```sh
FROM ft-rails:on-build
EXPOSE 3000
CMD ["rails", "s", "-b", "0.0.0.0", "-p" ,"3000"]
```
Your generic container must, from a ruby ​​container, install all the necessary dependencies, then copy your rails application to the / opt / app folder of your container. At build, Docker must install specific gems, as well as migrations and population of the db of your application. The Dockerfile-son will have to expose the right ports and launch the railserver (see example above). If you do not know the commands, it's time to take a look at the Ruby on Rails doc

4. Docker can be handy for testing an application still under development without creating pollution in your files. You will also have to design a Dockerfile which, in the build, retrieves the current version of Gitlab - Community Edition installs it with all the dependencies and the necessary configurations and launches the application (HTTPS and SSH). The container is considered valid, if you can access the web client, and if you are able to use correctly with Gitlab and interact via GIT with this container. Of course, you will not have to use the official container of Gitlab, it would be a little cheat ...
