# GameProject
 
```
Họ và tên: Dương Gia Bảo
Lớp: K68CA1
MSSV: 23021475
```

### | Chủ đề Game: Mini Golf by dgb
Đây là một game giả lập chuyển động của quả bóng Golf bằng cách **kéo thả chuột** để định hướng và căn chỉnh lực cho quả bóng di chuyển. Game có 5 level chơi, trong các level sẽ có những vật cản như những **viên đá** sẽ làm quả bóng bật lại khi chạm vào, **slime** sẽ làm chậm tốc độ di chuyển quả bóng, **xương rồng** khi chạm vào thì người chơi sẽ thua cuộc. Người chơi sẽ chiến thắng khi đi qua hết **5 level**.

![menu](screenshots\\menu.png)

#### | Ngưỡng điểm sinh viên cho là xứng đáng: 8.5
```
Lý do:
- Đây là game sinh viên tự làm
- Game có sử dụng các thư viện SDL mở rộng (SDL_image, SDL_mixer, SDL_ttf)
- Thuật toán về chuyển động của game được sinh viên tự sáng tạo và áp dụng
- Game của sinh viên là game có đồ họa tự thiết kế
```

## | Tổng quan về Gameplay

#### Kéo thả chuột để quả bóng di chuyển
![align](screenshots\\align.gif)

#### Di chuyển va chạm vào hòn đá
![collide](screenshots\\collide.gif)

#### Di chuyển vào vùng slime
![slime](screenshots\\slime.gif)

#### Nhặt box thêm thời gian
![collect](screenshots\\collect.gif)

#### Xương rồng
![cactus](screenshots\\cactus.gif)

#### Thắng level
![winLevels](screenshots\\winLevels.gif)

#### Đếm ngược thời gian
![countdown](screenshots\\countdown.gif)

Đây là toàn bộ những cơ chế cơ bản có trong game giúp đa dạng lối chơi và độ khó. Người chơi cần chọn cách di chuyển và căn chỉnh lực khéo léo để vượt qua các thử thách của trò chơi.

#### Điều kiện chiến thắng: vượt qua toàn bộ 5 level

# | Tài nguyên
1. Đồ họa:
- Đa số đồ họa đều được sinh viên tự tay vẽ và thiết kế (có sử dụng các ứng dụng như Adobe Fresco, Canva...)
- Một số hình ảnh ở trong game được lấy từ [itch.io](https://itch.io/), [freepik](https://www.freepik.com)

2. Thuật toán, source code:
- Cơ chế, ý tưởng: game [TwiniGolf](https://www.youtube.com/watch?v=iEn0ozP-jxc) từ kênh Youtube [PolyMars++](https://www.youtube.com/@PolyMarsLIVE)
- Thuật toán: tự xây dựng dựa trên kiến thức toán học, vật lý, tham khảo từ mentor, StackOverFlow, ChatGPT,...
- Nguồn học thư viện: tài liệu môn học, [lazyfoo](https://lazyfoo.net/), [SDLWiki](https://wiki.libsdl.org/SDL2/CategoryAPI), StackOverFlow