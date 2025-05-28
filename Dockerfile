FROM archlinux:latest

RUN pacman -Syu --noconfirm \
    gcc cmake make libpqxx postgresql git

WORKDIR /app
COPY . /app
RUN cmake -Bbuild && cmake --build build

CMD ["./build/cppcrudbp"]
