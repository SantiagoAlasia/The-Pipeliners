savedcmd_gpio_driver.mod := printf '%s\n'   gpio_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > gpio_driver.mod
