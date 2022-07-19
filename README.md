# philosophers &middot; [![Norminette](https://github.com/EnriqueSLeeK/philosophers/actions/workflows/norminette.yml/badge.svg)](https://github.com/EnriqueSLeeK/philosophers/actions/workflows/norminette.yml) &middot; [![make-test](https://github.com/EnriqueSLeeK/philosophers/actions/workflows/build.yml/badge.svg)](https://github.com/EnriqueSLeeK/philosophers/actions/workflows/build.yml)

A classic problem about synchronization issues and techniques

## Mandatory section
 - It's about thread synchronization
### Building
```
make -C philo
```

## Bonus section
 - It's about process synchronization
### Building
```
make -C philo_bonus
```

## Usage
```
<binary name> <number of phil> <time to die> <time to eat> <time to sleep> <min n times eat>
```
### Example
```
./philo 5 1000 300 300
./philo 5 1000 300 300 5
```
