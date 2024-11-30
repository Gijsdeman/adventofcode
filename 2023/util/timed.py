import time

def timed(f, *args, **kwds):
  start = time.time()
  result = f(*args, **kwds)
  elapsed = time.time() - start
  print("%s: %s" % (f.__name__, formatTime(elapsed)))
  return result

def formatTime(elapsed):
  if elapsed < 1e-9:
    return f"{elapsed * 1e9:.4f}ns"
  elif elapsed < 1e-6:
    return f"{elapsed * 1e6:.4f}μs"
  elif elapsed < 1e-3:
    return f"{elapsed * 1e3:.4f}ms"
  elif elapsed < 1:
    return f"{elapsed:.4f}s"
  elif elapsed < 60:
    return f"{elapsed / 60:.4f}m"