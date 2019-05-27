from datetime import datetime
class Menu:
 def __init__(self, name, items, start_time, end_time):
  self.name = name
  self.items = items
  self.start_time = start_time
  self.end_time = end_time
 
 def calculate_bill(self,purchased_items):
  self.purchased_items = purchased_items
  total = 0
  for item in  self.purchased_items:
    total += self.items[item]
  return total
 
 def __repr__(self):
  txt = "{} menu available from {} to {}".format(self.name, self.start_time, self.end_time)
  return txt
  
  
brunch_items = {
  'pancakes': 7.50, 'waffles': 9.00, 'burger': 11.00, 'home fries': 4.50, 'coffee': 1.50, 'espresso': 3.00, 'tea': 1.00, 'mimosa': 10.50, 'orange juice': 3.50
}
early_bird_item = {
  'salumeria plate': 8.00, 'salad and breadsticks (serves 2, no refills)': 14.00, 'pizza with quattro formaggi': 9.00, 'duck ragu': 17.50, 'mushroom ravioli (vegan)': 13.50, 'coffee': 1.50, 'espresso': 3.00,
}
dinner_items = {
  'crostini with eggplant caponata': 13.00, 'ceaser salad': 16.00, 'pizza with quattro formaggi': 11.00, 'duck ragu': 19.50, 'mushroom ravioli (vegan)': 13.50, 'coffee': 2.00, 'espresso': 3.00,
}
kids_items = {
  'chicken nuggets': 6.50, 'fusilli with wild mushrooms': 12.00, 'apple juice': 3.00
}
 
brunch_menu = Menu('brunch',brunch_items,1100,1600)
bill1 = brunch_menu.calculate_bill(['pancakes', 'home fries', 'coffee'])
print(brunch_menu)
print(bill1)

Early_bird_Menu = Menu('early_bird',early_bird_item,1500,1800)
bill2 = Early_bird_Menu.calculate_bill(['salumeria plate','mushroom ravioli (vegan)'])
print(bill2)
dinner_Menu = Menu('dinner',dinner_items,1700,2300)
kids_Menu = Menu('kids',kids_items,1100,2100)


class Franchise:
 def __init__(self,address,menus):
  self.address = address
  self.menus = menus
 def __repr__(self):
  return self.address 
 def available_menus(self, time):
  temp = []
  for menu in self.menus:
   if time >= menu.start_time and time <=menu.end_time:
    temp.append(menu)
  return temp
    
    
    
    
flagship_store= Franchise("1232 West End Road",[brunch_menu,Early_bird_Menu,dinner_Menu,kids_Menu])


new_installment= Franchise("12 East Mulberry Street",[brunch_menu,Early_bird_Menu,dinner_Menu,kids_Menu])

available_M = flagship_store.available_menus(1200)



arepas_items = {
  'arepa pabellon': 7.00, 'pernil arepa': 8.50, 'guayanes arepa': 8.00, 'jamon arepa': 7.50
}
arepas_menu = Menu('arepas',arepas_items,1000,2000)

arepas_place = Franchise("189 Fitzgerald Avenue",arepas_menu)



#print(available_M)
print(flagship_store.available_menus(1700))

class Business:
 def __init__(self,name, franchises):
  
  pass


myBusiness= Business("Basta Fazoolin\' with my Heart",[flagship_store,new_installment])



Take_a_Arepa = Business("Take a' Arepa",arepas_place)

