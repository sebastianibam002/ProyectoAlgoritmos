import matplotlib.pyplot as plt
import numpy as np

dic = {5:0,8:0,11:0,13:0,15:0,17:0,18:0,19:0,20:0,23:0,25:0,27:0,41:0,44:0,47:0,50:0,52:0,54:0,63:0,66:0,68:0,70:0,73:0,76:0,81:0,85:0,86:0,88:0,91:0,94:0,95:0,97:0,99:0}
def obtenerInfo():
    f = open("vis.txt","r")
    antioquia=[];#05==0(247,354)
    atlantico={};#08==1(272,118)
    bogota= [];#11==2(323,480)
    bolivar={};#13==3(314,259)
    boyaca={};#15==4(380,422)
    caldas={};#17==5(248,434)
    caqueta={};#18==(304,693)
    cauca={};#19==7(143,596)
    cesar={};#20==8(346,196)
    cordova={};#23(230,258)
    cundinamarca={};#25(312,451)
    choco=[]#27(160,424)
    huila=[]#41(236,594)
    la_guajira=[]#44(391,90)
    magdalena=[]#47(309,149)
    meta=[]#50(367,551)
    narino=[]#52(93,643)
    norte_de_santander=[]#54(399,274)
    quindio=[]#63(228,484)
    risaralda=[]#66(206,440)
    santander=[]#68(368,358)
    sucre=[]#70(266,218)
    tolima=[]#73(252,523)
    valle_del_cauca=[]#76(172,537)
    arauca=[]#81(507,358)
    casanare=[]#85(476,435)
    putumayo=[]#86(236,725)
    san_andres=[]#88(121,88)
    amazonas=[]#91(474,833)
    guainia=[]#94(634,586)
    guaviare=[]#95(439,658)
    vaupes=[]#97(527,702)
    vichada=[]#99(592,469)

    contents = f.readlines()
    
    for line in contents:
        line = line.replace("\n", "")
        if int(line) in dic.keys():
            dic[int(line)] += 1
        
    
    print(dic)       





obtenerInfo()



rng = np.random.RandomState(0)

col_img = plt.imread("Colombia.png")
plt.figure(figsize=(20, 10))


"""" LISTAS CON VALORES DETERMINADOS """
x = [247,272,323,314,380,248,304,143,346,230,312,160,236,391,309,367,93,399,228,206,368,266,252,172,507,476,236,121,474,634,439,527,592]
y = [354,118,480,259,422,434,693,596,196,258,451,424,594,90,149,551,643,274,484,440,358,218,523,537,358,435,725,88,833,586,658,702,469]


""" 1000 numeros aleatorios"""
#x = np.random.normal(300, 100, 100)
#y = np.random.normal(400, 200, 100)

########################## OPCION 1 ################################

listaSizes = []
for a in dic.values():
    listaSizes.append(a)
colors = listaSizes;

print(colors)

#print(dic.values())
sizes = listaSizes
plt.scatter(x, y, c=colors, s=sizes, alpha=0.3, cmap='viridis')
plt.colorbar()
plt.imshow(col_img)
plt.show()

########################## OPCION 2 ################################

#plt.scatter(x, y)
#plt.imshow(col_img)


