import requests

r = requests.get('https://apnews.com/VirusOutbreak')

from bs4 import BeautifulSoup as bs

soup = bs(r.text, 'html.parser') 
link_elements = soup.find_all(
    'a', attrs={"class":'Component-headline-0-2-92'}
)

links = {}
for e in link_elements:
    title = e.text
    article_link = 'http://apnews.com' + e['href']
    links[title] = article_link

example_title = list(links.keys())[0]
print (f'There are {len(links)} links')
print (f'An example of links:')
print (f'\t{example_title}')
print (f'\t{links[example_title]}')

import time
for title in links:
    with open(f'{title}.txt', 'w') as f:
        r = requests.get(links[title])
        soup = bs(r.text, 'html.parser') 
        f.write(soup.text)

    time.sleep(10)