Drone Mission Control and Energy Safety Logic
Bu proje, bir İHA'nın görev noktaları arasında uçuş yaparken pil seviyesini kontrol eden ve aracın kırıma uğramasını engelleyen bir güvenlik algoritmasıdır. 

Teknik Detaylar

Memory: Gömülü sistem kısıtları nedeniyle dinamik bellek (malloc/free) kullanılmamıştır; tüm veriler stack üzerindedir. 

Data Transfer: Fonksiyonlara veri gönderilirken bellek kopyalamasının (copy-by-value) önüne geçmek için pointer (pass-by-reference) kullanılmıştır. 

Safety Logic: check_safety fonksiyonu, drone bir sonraki hedefe gitmeden önce "Hedef + Home" mesafesini hesaplar ve pilin yetmeyeceği durumlarda görevi reddederek Return-to-Home (RTH) komutunu tetikler. 

Proje Yapısı

Point ve Drone struct yapıları ile koordinat ve sistem verileri yönetilir. 

get_distance fonksiyonu ile iki nokta arasındaki Öklid mesafesi hesaplanır. 

Main döngüsü içinde pointer aritmetiği kullanılarak waypoint dizisi taranır.
