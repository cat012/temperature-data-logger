import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

y = np.genfromtxt("result.txt", delimiter='\n', dtype=np.integer, skip_footer=1)
l = len(y)+1
x = np.arange(1, l)

fig, ax = plt.subplots()

ax.stackplot(x, y/10, color='mediumslateblue')

ax.xaxis.set_major_locator(ticker.MultipleLocator(60))
ax.xaxis.set_minor_locator(ticker.MultipleLocator(10))
    
ax.yaxis.set_major_locator(ticker.MultipleLocator(10))
ax.yaxis.set_minor_locator(ticker.MultipleLocator(1))

ax.grid(which='major', color = 'lightgray', linestyle = '-', linewidth=0.5)
ax.grid(which='minor', color = 'lightgray', linestyle = '-', linewidth=0.2)

ax.tick_params(which='major', length=6, width=0.8)
ax.tick_params(which='minor', length=2, width=0.4)

ax.set_facecolor('ghostwhite')
fig.set_facecolor('aliceblue')
fig.set_figwidth(9)
fig.set_figheight(5)

plt.show()


