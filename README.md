# Panoramix

**Panoramix** is a multithreaded simulation in C where villagers drink magic potions to fight Romans. The druid refills the pot when needed. This project demonstrates thread synchronization with mutexes and semaphores.

---

## 🧩 Project Description

- Each villager runs in its own thread.
- The druid also runs in a separate thread.
- Villagers drink potion before fighting; if the pot is empty, they wake up the druid.
- The druid refills the pot a limited number of times.
- The program ends gracefully when all villagers are done fighting and the druid is out of ingredients.

---

## 🎯 Goals

- Practice thread management with `pthread`.
- Implement synchronization using `mutex` and `semaphore`.
- Handle asynchronous events properly.
- Avoid deadlocks and infinite waits.

---

## ⚙️ Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/Enoal-Fauchille-Bolle/panoramix.git
   cd panoramix
   ```

2. Compile the project using `make`:
   ```bash
   make
   ```

Available Makefile rules:
- `make`: builds the program
- `make clean`: removes object files
- `make fclean`: removes all compiled files and the binary
- `make re`: cleans and rebuilds the project

---

## 🚀 Usage

```bash
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

Arguments:
- `nb_villagers`: Number of villagers (>0)
- `pot_size`: Initial capacity of the pot (>0)
- `nb_fights`: Number of fights per villager (>0)
- `nb_refills`: Number of refills available to the druid (>0)

Example:
```bash
./panoramix 3 5 3 2
```

If invalid arguments are provided, the program will print a usage message and exit with code `84`.

---

## 📄 License

This project is under the **MIT License**.
See [LICENSE](LICENSE) for details.

---

## 🤝 Contributing

Feel free to fork the project, open issues, or submit pull requests.
Contributions that improve the code structure, fix bugs, or enhance the README are welcome!