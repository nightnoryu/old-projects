# urlshortener
Bare-bones URL shortening microservice. That's it.

## Routes
- `POST /save` - save the URL and get the shortened version.

Request:
```json
{
  "url": "https://github.com"
}
```

Response:
```json
{
  "short": "tuzsnebf",
  "expanded": "https://github.com"
}
```

- `GET /expand/{url}` - expand the provided short URL.

Response:
```json
{
  "short": "tuzsnebf",
  "expanded": "https://github.com"
}
```

- `GET /resolve/{url}` - redirect by the short URL.
