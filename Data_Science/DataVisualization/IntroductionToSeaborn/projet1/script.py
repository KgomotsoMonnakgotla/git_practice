from matplotlib import pyplot as plt
import pandas as pd
import seaborn as sns

df = pd.read_csv('WorldCupMatches.csv')

df['Total Goals'] = df['Home Team Goals'] + df['Away Team Goals']
print(df.head())
sns.set_style('whitegrid')
sns.set_context('poster')
f, ax = plt.subplots(figsize=(12,7))
ax = sns.barplot(data=df,
                 x=df.Year,
                 y=df['Total Goals']
)
ax.set_title('Average Number Of Goals Scored In World Cup Matches By Year')
plt.show()

df_goals = pd.read_csv('goals.csv')
print(df_goals.head())
sns.set_context()
sns.set_context("notebook", font_scale = 1.25)
f, ax2 = plt.subplots(figsize=(12,7))
sns.boxplot(data=df_goals,
            x=df_goals.year,
            y=df_goals.goals,
            palette ='Spectral'            
)
ax2.set_title('Number Of Goals Scored In World Cup Matches By Year')
plt.show()

