# cppbdd
This is a team final project for the Software Testing class, developed by [@smb374](https://github.com/smb374) and [me](https://github.com/Alan-Kuan).
We utilized TDD (Test-Driven Development) to create a BDD (Behavior-Driven Development) Framework using C++.
We found the idea of testing the project on its own to be enjoyable, so we enthusiastically delved into its development.

## Build
We provided a containerized environment for easily building the project.
You can use either Docker Compose or Podman Compose to activate the environment.

For example you can type:
```sh
docker compose up -d
```

After the container is created, an SSH server starts in the container.

We can simply connect into the container with:
```sh
ssh localhost -p 22722
```

The default password is `pass`.

Inside the container, the project has already been mounted, and we're just in the project's root. Then, simply type the following command:
```sh
make config && make
```

We first setup the build directory for Meson, and start to build the project.

To test our project, the following command can be used.
```sh
make test
```

Though our project's dependency `inja` will also get tested.

## Examples
We provided some examples of how to use the framework under the directory [`examples`](examples).
