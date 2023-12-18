# Algorithm Visualizer

[Project Report](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/blob/report/Project%20Report.pdf)

## Run Locally
> Note: If you are using GNU GCC compiler on Windows, you may need the winlibs build of the compiler. You can download it from [here](https://winlibs.com/).
<!-- Say project is setup with cmake and give link -->
The project is setup with [cmake](https://cmake.org/). To run the project locally, follow the steps below:

- Clone the repository

```bash
  git clone https://github.com/pr-a-sh-ant/Algorithm-Visualizer.git
  cd Algorithm-Visualizer
```

- Run cmake
> Note: The build system can be changed by specifying the generator flag. For example, to use MinGW MakeFiles build system, add `-G "MinGW Makefiles"` to the cmake command.
```
  cmake -S . -B build
  cmake --build build --config Release
```

- Run the executable
> Note: The executable path may vary depending on the OS and the build system used.
```
  ./build/AlgViz
```

## Screenshots
![Home Page](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/raw/report/screenshots/Home%20Page.png)
![Maze Gneration](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/raw/report/screenshots/Maze%20Generation.png)
![Search Complete](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/raw/report/screenshots/Search%20Complete.png)
![Sort Page](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/raw/report/screenshots/Sort%20Page.png)
![Sorting](https://github.com/pr-a-sh-ant/Algorithm-Visualizer/raw/report/screenshots/Sorting.png)

## Contributors

* [Kirtan Kunwar](https://github.com/kiyotone)
* [Navin Nepal](https://github.com/marconn01)
* [Prashant Aryal](https://github.com/pr-a-sh-ant)
* [Prateek Poudel](https://github.com/Prateek61)
