#!/usr/bin/env python
import sys
import re

#Global address db
address_db = {}

def parseAddress(address):
  #Only commands a,c,r are permissive
  coordinates = []
  if address[0] == 'r':
    rm_street = re.compile(r"([r])(\s+\"[A-Za-z\s]+\")") #Regex
    matches = rm_street.match(address)
    if rm_street.match(address):
      groups = matches.groups()
      name = groups[1].strip().lower() #Street name
      validate = address.split(groups[1].strip())
      if validate[1] != '':
        print('Error: An extra string came after street street name',file=sys.stderr)
      else:
        if name in address_db:
          address_db.pop(name)
        else:
          print("Error: Address can't be removed as it doesn't exist",file=sys.stderr)
    else:
      print("Error: invalid input", file=sys.stderr)
  else:
    street = re.compile(r"([ac])(\s+\"[A-Za-z\s]+\s*\"\s*) ((\(\s*-?\d+\s*,\s*-?\d+\s*\)\s*)*)")
    matches = street.match(address)
    if street.match(address):
      groups = matches.groups()
      name = groups[1].strip().lower()
      valid = address.split(groups[1].strip())
      st = ''
      tc = ''
      for s in valid[1]:
        if s == ' ':
          continue
        st+=s
      coordinate_str = re.findall(r'(\(\s*-?\d+\s*,\s*-?\d+\s*\))', groups[2])
      temp_coord_str = ''.join(coordinate_str)
      for t in temp_coord_str:
        if t != ' ':
          tc+=t
      cord_valid = st.strip().split(tc.strip())
      if cord_valid[0] != '' or cord_valid[1] != '':
        print('Error: Enter valid coordinates',file=sys.stderr)
      else:
        for coord in coordinate_str:
          coord = coord.replace('(', '').replace(')', '').strip()
          temp_coord = coord.split(",")
          coordinates.append([int(temp_coord[0]), int(temp_coord[1])])
        if address[0] == 'a': #Add address
          if name not in address_db:
            address_db[name] = coordinates
          else:
            print('Error: Address already exists',file=sys.stderr)
        else: #This works on change address
          if name in address_db:
            address_db[name] = coordinates
          else:
            print("Error: Trying to change an address that doesn't exist",file=sys.stderr)
    else:
      print("Error: invalid input", file=sys.stderr)

def intersection(P1,P2,P3,P4):
  x1,y1 = P1
  x2,y2 = P2
  x3,y3 = P3
  x4,y4 = P4

  a1 = y2 - y1
  b1 = x1 - x2
  c1 = (a1 * x1) + (b1 * y1)
  a2 = y4 - y3
  b2 = x3 - x4
  c2 = (a2 * x3) + (b2 * y3)
  numerator1 = float((b2 * c1) - (b1 * c2))
  numerator2 = float((a1 * c2) - (a2 * c1))
  denominator = float((a1 * b2) - (a2 * b1))
  if denominator == 0:
      return [None, None]

  # intersecting coordinates
  xa = numerator1 / denominator
  x = round(xa, 2)
  if x.is_integer():
   x = int(x)
  ya = numerator2 / denominator
  y = round(ya, 2)
  if y.is_integer():
    y = int(y)
  if (x2 - x1) == 0:
      rx0 = -1
  else:
      rx0 = (x-x1) / (x2-x1)
  if (y2 - y1) == 0:
      ry0 = -1
  else:
      ry0 = (y-y1) / (y2-y1)
  if (x4 - x3) == 0:
      rx1 = -1
  else:
      rx1 = (x-x3) / (x4-x3)
  if (y4 - y3) == 0:
      ry1 = -1
  else:
      ry1 = (y-y3) / (y4-y3)
  if (0 <= rx0 <= 1 or 0 <= ry0 <= 1) and (0 <= rx1 <= 1 or 0 <= ry1 <= 1):
      return [x, y]
  else:
      return [None, None]

def isCollinear(p1,p2,p):
  x1,y1 = p1
  x2,y2 = p2
  x,y = p
  crossproduct = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)
  # compare versus epsilon = 0.03 for floating point values, or != 0 if using integers
  #Absolute value of crossproduct return the area of the parallelogram spaned by the two 
  #vectors 
  if abs(crossproduct) > 0.03: #0.0000001 0.03
      return False
  dotproduct = (x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)
  if dotproduct < 0:
      return False
  squaredlengthba = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)
  if dotproduct > squaredlengthba:
      return False
  return True

def graph():
  getIntersects = set()
  getVertices = set()
  temp = 0
  possible_edges = set()
  
  
  V =[]
  for street1 in address_db:
    street_coordinates = address_db[street1]
    for i in range(len(street_coordinates)-1):
      for street2 in address_db:
        if street1== street2:
          continue
        street_coordinates2 = address_db[street2]
        for j in range(len(street_coordinates2) - 1):
          if (isCollinear(street_coordinates[i],street_coordinates[i+1],street_coordinates2[j])):
            possible_edges.add((tuple(street_coordinates[i]),tuple(street_coordinates2[j])))
            possible_edges.add((tuple(street_coordinates2[j]),tuple(street_coordinates[i+1])))
            getVertices.add(tuple(street_coordinates[i]))
            getVertices.add(tuple(street_coordinates[i+1]))
            getVertices.add(tuple(street_coordinates2[j]))
          if(isCollinear(street_coordinates2[j],street_coordinates2[j+1],street_coordinates[i+1])):
            possible_edges.add((tuple(street_coordinates2[j+1]),tuple(street_coordinates[i+1])))
            getVertices.add(tuple(street_coordinates[i+1]))
            getVertices.add(tuple(street_coordinates2[j]))
            getVertices.add(tuple(street_coordinates2[j+1]))

          intersect = intersection(street_coordinates[i],street_coordinates[i+1],street_coordinates2[j],street_coordinates2[j+1])
          if intersect[0] is not None:
            getIntersects.add(tuple(intersect))
            getVertices.add(tuple(intersect))
            getVertices.add(tuple(street_coordinates[i]))
            getVertices.add(tuple(street_coordinates[i+1]))
            getVertices.add(tuple(street_coordinates2[j]))
            getVertices.add(tuple(street_coordinates2[j+1]))
            possible_edges.add(tuple((tuple(intersect), tuple(street_coordinates[i]))))
            possible_edges.add(tuple((tuple(intersect), tuple(street_coordinates[i+1]))))
            possible_edges.add(tuple((tuple(intersect), tuple(street_coordinates2[j]))))
            possible_edges.add(tuple((tuple(intersect), tuple(street_coordinates2[j+1]))))
          for t in getIntersects:
            edgelist = list(possible_edges)
            for edge in edgelist:
              if t == edge[0]:
                continue
              if edge[0]==edge[1]:
                # print('I removed ', edge)
                possible_edges.remove(tuple(edge))
                continue

              if(isCollinear(edge[0],edge[1],t)):
        # if t != tuple(edge[0]):
                possible_edges.add((tuple(edge[0]),t))
        # if t != tuple(edge[1]):
                possible_edges.add((t,tuple(edge[1])))
                possible_edges.remove(tuple(edge))
                        
              if(isCollinear(edge[1],edge[0],t)):
                possible_edges.add((tuple(edge[1]),t))
                possible_edges.add((t,tuple(edge[0])))
                # print('I found an intersect lying between intersecting points') 
              if(isCollinear(edge[1],t,edge[0])):
                possible_edges.add((tuple(edge[1]),edge[0]))
                possible_edges.add((tuple(edge[0]),t))
                # print('I found an intersect point between') 
                    
    # while (len(possible_edges) != 0):
  # print(len(possible_edges))
  # print()
  # print()
  while(len(possible_edges) != temp):
    # print('ran')
    temp = len(possible_edges)
    for intersect in getIntersects:
      edgelist = list(possible_edges)
      for edge in edgelist:
        if intersect == edge[0]:
          continue
        if edge[0]==edge[1]:
          possible_edges.remove(tuple(edge)) 
          continue
        if(isCollinear(edge[0],edge[1],intersect)):
          possible_edges.add((tuple(edge[0]),intersect))
          possible_edges.add((intersect,tuple(edge[1])))
          possible_edges.remove(tuple(edge)) 

        if(isCollinear(edge[1],edge[0],intersect)):
          possible_edges.add((tuple(edge[1]),intersect))
          possible_edges.add((intersect,tuple(edge[0])))

 ####### Filter possible_edges ##########
  intersect = list(getIntersects)
  extraEdge = set()
  semi_final_edges = set()

  for lstEdge in possible_edges:
    quickCheck = list(lstEdge)
    verify=False
    for inst in intersect:
      if(inst not in quickCheck):
        if(isCollinear(quickCheck[0],quickCheck[1],inst)==True):
          verify=True   
    if(verify==False):
      semi_final_edges.add(tuple((tuple(quickCheck[0]), tuple(quickCheck[1]))))

#### Check for midpoint edges #######
  for street1 in address_db:
    street_coordinates = address_db[street1]
    
    for i in range(len(street_coordinates)-1): #for one street 
        tempNode = []
        for point in (intersect): #for one street segment 
            if(isCollinear(street_coordinates[i],street_coordinates[i+1],point)):
                tempNode.append(point)

        if(len(tempNode)<=1):
            pass
        elif(len(tempNode)==2):
            extraEdge.add(tuple((tuple(tempNode[0]), tuple(tempNode[1]))))
        else:

            allEdges = []
            for pt1 in tempNode:
                for pt2 in tempNode:
                    if ( (pt1 != pt2) and (len(allEdges)==0) ):
                        allEdges.append(tuple((tuple(pt1), tuple(pt2))))
                    elif(pt1 != pt2):
                        exists=False
                        for edg in allEdges:
                            quickCheck = list(edg)
                            if(pt1 in quickCheck):
                                if(pt2 in quickCheck):
                                    exists=True
                        if(exists==False):
                            allEdges.append(tuple((tuple(pt1), tuple(pt2)))) #adding only unique combinations
            #Ensuring that no interset falls on an edge
            for lstEdge in allEdges:
                quickCheck = list(lstEdge)
                verify=False
                for inst in intersect:
                    if(inst not in quickCheck):
                        if(isCollinear(quickCheck[0],quickCheck[1],inst)==True):
                            verify=True
                if(verify==False):
                    extraEdge.add(tuple((tuple(quickCheck[0]), tuple(quickCheck[1]))))
  finalEdge = set() #Final Edge SET 

#### Remove Duplicate from Both sets and merge into one set
  for sm in semi_final_edges:
    if(len(finalEdge)==0):
      finalEdge.add(sm)
    else:
      temp = list(sm)
      verify=False
      for e in finalEdge:
        temp2 = list(e)
        if(temp[0] in temp2):
          if(temp[1] in temp2):
            verify=True
      if(verify==False):
        finalEdge.add(tuple((tuple(temp[0]), tuple(temp[1]))))

  for ee in extraEdge:
    temp = list(ee)
    verify=False
    for e in finalEdge:
        temp2 = list(e)
        if(temp[0] in temp2):
          if(temp[1] in temp2):
            verify=True
    if(verify==False):
      finalEdge.add(tuple((tuple(temp[0]), tuple(temp[1]))))

  V = list(getVertices)
  V_size = len(list(getVertices))
  print(f'V  {V_size} \n')
  list_finalEdge = list(finalEdge)
  # print('E = {')
  # for i,e in enumerate(finalEdge):
  #     print(f'<{V.index(e[0])},{V.index(e[1])}>,')
  # print('}')
  
  e_val = "E {"
  for i,e in enumerate(list_finalEdge):
    e_val1 = V.index(e[0])
    str_e_val1 = str(e_val1)
    e_val2 = V.index(e[1])
    str_e_val2 = str(e_val2)  
    if(e in list_finalEdge[:-1]):
      e_val +="<"+ str_e_val1 + "," + str_e_val2 + ">"+","
    else:
      e_val +="<"+ str_e_val1 + "," + str_e_val2 + ">" 
  e_val += "}" 
  sys.stdout.write(e_val+"\n")
  sys.stdout.flush()
  # address_db.clear() #Clears DB after creating graph

def main():
  while True:
    address = sys.stdin.readline()
    if address == '' or address[0] == '\n':
        break
    address = address.strip()
    if address[0] == 'a' or address[0] == 'c' or address[0] == 'r':
      parseAddress(address)
    elif address[0] == 'g':
      graph()
    else:
        print("Error: please use the right command", file=sys.stderr)
  sys.exit(0)
if __name__ == '__main__':
  try:
    main()
  except EOFError:
    sys.exit(0)
