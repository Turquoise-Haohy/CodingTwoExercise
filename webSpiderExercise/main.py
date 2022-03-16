# This is a spider test

# written by Hanyi HAO
# downloading music files from Netease music website, since spotify is anti-spider TAT


import requests
import os
import re

filename = "music\\"

if not os.path.exists(filename):
 os.mkdir(filename)

url = 'https://music.163.com/discover/toplist?id=3779629'

headers = {
'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.109 Safari/537.36'
}
response = requests.get(url=url, headers=headers)
# print(response.text)

html_data = re.findall('<li><a href="/song\?id=(\d+)">(.*?)</a>', response.text)
for num_id, title in html_data:
 music_url = f'http://music.163.com/song/media/outer/url?id=(num_id).mp3'
 music = requests.get(url=music_url,headers=headers).content
 with open(filename+title+'.mp3',mode='wb') as f:
  f.write(music)
 print(num_id, title)