#import codecademylib3_seaborn

# Add your code below:
from matplotlib import pyplot as plt
import random

numbers_a = range(1,13)

numbers_b =[random.randint(1,1000) for i in numbers_a]

plt.plot(numbers_a,numbers_b) 

plt.show()






















