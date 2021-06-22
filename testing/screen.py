import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv('screen.csv')
df['SCREEN_WIDTH'] = df['BOARD_WIDTH'] * df['BLOCK_SIZE']
df['SCREEN_HEIGHT'] = df['BOARD_HEIGHT'] * df['BLOCK_SIZE']
df['SCREEN_SIZE'] = df['SCREEN_WIDTH'] * df['SCREEN_HEIGHT']
# print(df.to_string())

dfT = df[df['WORKED'] == True]
dfF = df[df['WORKED'] == False]

x = np.arange(5,50)
y = np.arange(5,200)
X, Y = np.meshgrid(x, y)
z = (37**2)/Y

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot_surface(X, Y, z)
ax.scatter(dfT['BLOCK_SIZE'], dfT['BOARD_WIDTH'], dfT['BOARD_HEIGHT'], marker='o')
ax.scatter(dfF['BLOCK_SIZE'], dfF['BOARD_WIDTH'], dfF['BOARD_HEIGHT'], marker='^')
ax.set_xlabel('BLOCK_SIZE')
ax.set_ylabel('BOARD_WIDTH')
ax.set_zlabel('BOARD_HEIGHT')

plt.show()

# plt.plot(np.arange(10,5000),1/np.arange(10,5000))
# plt.scatter(dfT['SCREEN_WIDTH'], dfT['SCREEN_HEIGHT'], marker='o')
# plt.scatter(dfF['SCREEN_WIDTH'], dfF['SCREEN_HEIGHT'], marker='^')
# plt.show()

# plt.scatter(dfT['SCREEN_SIZE'], dfT['WORKED'], marker='o')
# plt.scatter(dfF['SCREEN_SIZE'], dfF['WORKED'], marker='^')
# plt.show()

# x = np.arange(10,5000)
# y = np.arange(10,5000)
# X, Y = np.meshgrid(x, y)
# z = (X*Y)
# 
# fig1 = plt.figure()
# ax1 = fig1.add_subplot(projection='3d')
# # ax1.plot_wireframe(X, Y, z)
# # ax1.contour3D(X, Y, z, 50, cmap='binary')
# ax1.scatter(dfT['SCREEN_WIDTH'], dfT['SCREEN_HEIGHT'], dfT['SCREEN_SIZE'], marker='o')
# ax1.scatter(dfF['SCREEN_WIDTH'], dfF['SCREEN_HEIGHT'], dfF['SCREEN_SIZE'], marker='^')
# ax1.set_zlabel('SCREEN_SIZE')
# ax1.set_xlabel('BOARD_WIDTH')
# ax1.set_ylabel('BOARD_HEIGHT')
# plt.show()

print(dfT.to_string())
print(dfF.to_string())
