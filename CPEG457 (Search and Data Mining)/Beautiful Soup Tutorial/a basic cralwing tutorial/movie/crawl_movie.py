import requests

r = requests.get(
    'https://www.rottentomatoes.com/top/bestofrt/'
)

from bs4 import BeautifulSoup as bs

soup = bs(r.text, 'html.parser') 
table = soup.find(
    'table', attrs={"class":'table'}
)

link_elements = table.find_all(
    'a', attrs={"class":'unstyled articleLink'}
)

links = {}
for e in link_elements:
    title = e.text.strip()
    article_link = 'https://www.rottentomatoes.com/' 
    article_link += e['href']
    links[title] = article_link

example_title = list(links.keys())[0]
print (f'There are {len(links)} links')
print (f'An example of links:')
print (f'\t{example_title}')
print (f'\t{links[example_title]}')

import time
import json
for title in links:
    with open(f'{title}.json', 'w') as f:
        r = requests.get(links[title])
        soup = bs(r.text, 'html.parser') 
        synopsis = soup.find(
            'div', attrs={"id":'movieSynopsis'}
        )
        data = {'synopsis': synopsis.text}
        json.dump(data, f)

    time.sleep(10)
