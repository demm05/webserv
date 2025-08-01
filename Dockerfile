FROM alpine:3.22.0 AS builder

WORKDIR /app

RUN apk update && \
    apk add --no-cache cppcheck make g++

COPY Makefile ./
COPY mk ./mk/
COPY inc ./inc/
COPY src ./src/

RUN make all

FROM alpine:3.22.0

RUN apk update && \
    apk add --no-cache libstdc++

WORKDIR /app

COPY --from=builder /app/webserv .

EXPOSE 443

CMD ["./webserv"]
