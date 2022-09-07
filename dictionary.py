# -*- coding: utf-8 -*-
"""
Created on Sat Oct 23 09:39:09 2021

@author: mayag
"""

'''
Reading the file
'''
list_values=[]
list_keys=[]
with open('DIC(A).txt', 'r') as reader:
    for line in reader:
        if len(line.split()) == 0:
            continue
        list_1=line.split('(')
        key=list_1[0].strip()
        value='('+'('.join(list_1[1:])
        list_values.append(value)
        list_keys.append(key)
'''
Creating lists with all words, with all possible meanings, and how many meanings each words has 
'''

how_many=[]
words=[]
meanings=[]

i=0
while i<len(list_keys):
    meaning=[]
    hm=list_keys.count(list_keys[i])
    how_many.append(hm)
    words.append(list_keys[i])
    for j in range(hm):
        meaning.append(list_values[0])
        list_values.pop(0)
    meanings.append(meaning)
    i+=hm
'''
Setting up dictionary
'''
dictionary={}
for i in range(len(words)):
    dictionary[words[i].lower()]='\n'+'\n'.join(meanings[i])

'''
The program inputing user words and adds them to a new list with user inputed words
'''
user_input=''
list_user=[]
while 1:
    user_input=input('Input word:\n')
    if user_input=='q':
        break
    try:
        print(dictionary[user_input.lower()])
        if user_input.lower() not in list_user:
            list_user.append(user_input.lower())
    except KeyError:
        print('Ooops! There is no such word! Try again')
      
'''
Creating a file with user-inputed words
'''
with open('words.txt','a') as newFile:
    for i in range(len(list_user)):
        newFile.write(list_user[i].lower()+'\n')
        


