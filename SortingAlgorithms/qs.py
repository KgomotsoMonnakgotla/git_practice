def quicksort(list, start, end):
  if start >= end:
    return

  print(list[start])
  start += 1
  quicksort(list, start, end)

colors = ["blue", "red", "green", "purple", "orange"]
quicksort(colors, 0, len(colors) - 1)
