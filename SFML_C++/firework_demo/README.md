Fireworks Demo
-----------------

This is a revised version of [Fireworks Demo](https://github.com/Penaz91/firework_demo) rewritten for the "2D Game Development: From Zero To Hero Companion" repository project.

The original version is still available under the "Unlicense" license at the link above.

Game Loop
----------

Clicking somewhere on the window will shoot a firework on that place, using ease-out functions.

When the firework explodes, particles will be emitted to match a certain shape, randomly chosen from the `resources/patterns` directory.

Patterns
---------

Shapes can be edited and added in the `resources/patterns` directory.

Each black pixel represents a random color particle. Transparent pixels won't create particles. Colored pixels will have their color taken as-is and used to create the particles.

Building the project
---------------------

Dependencies:

- A compiler that supports C++17's `<filesystem>` (GCC 16 or newer should suffice);
- SFML version 3.0 or higher (might not work with a future "SFML 4" version, due to API breakage).

To build the project, just open a terminal on the root of the project and type

```.sh
make
```

A new file called `main.bin` will appear, you may need to give it execution permissions using

```.sh
chmod +x ./main.bin
```

After that, you can run the demo by just typing

```.sh
./main.bin
```
