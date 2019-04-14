import psutil
import os,datetime,time
import socket

def getMemCpu():
 data = psutil.virtual_memory()
 total = data.total #总内存,单位为byte
 free = data.available #可用内存
 s1 = psutil.net_io_counters(pernic=True)['以太网']
 s2 = psutil.net_io_counters(pernic=True)['以太网']
 result = s2.bytes_recv - s1.bytes_recv#除法结果保留两位小数

# memory = "Memory usage:%d"%(int(round(data.percent)))+"%"+" "
# cpu = "CPU:%0.2f"%psutil.cpu_percent(interval=1)+"%"+" "
# netspeed = "Net speed:" + str('%.2f'%(result / 1024)) + 'kb/s'
 id = "1"+" "
 memory = "%d"%(int(round(data.percent)))+" "
 cpu = "%0.2f"%psutil.cpu_percent(interval=1)+" "
 netspeed ="%0.2f"%(result / 1024)
 return id+memory+cpu+netspeed

def main():

 while(True):
  time.sleep(0.2)
  info = getMemCpu()
  info_bytes = bytes(info,"utf8")
  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s.sendto(info_bytes, ('127.0.0.1', 23333))

  print(info +"\b"*(len(info)+1))

if __name__=="__main__":
 main()
