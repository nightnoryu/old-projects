package domain

import "encoding/json"

type URL struct {
	short, expanded string
}

func (u *URL) Short() string {
	return u.short
}

func (u *URL) Expanded() string {
	return u.expanded
}

func (u *URL) MarshalJSON() ([]byte, error) {
	return json.Marshal(struct {
		Short    string `json:"short"`
		Expanded string `json:"expanded"`
	}{
		Short:    u.Short(),
		Expanded: u.Expanded(),
	})
}

func NewURL(short, expanded string) *URL {
	return &URL{
		short:    short,
		expanded: expanded,
	}
}
