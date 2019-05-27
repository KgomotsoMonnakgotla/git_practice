how_many_s = [{'s': False}, "sassafrass", 18, ["a", "c", "s", "d", "s"]]

for ss in how_many_s:
 if hasattr(ss,"count"):
  print(ss)
  print(ss.count('s'))
  
