# Group Label Shenanigans
adds group labels to more objects, some customization options, makes them not rotate, yk, shenanigans

also sowwy if extras colors are like random theres a reason u can change these thngs

***you dont get much named editor groups support until its mod dev fixes it for mac, if ur a windows dev make a pr or smth idk***

## JSON
u can customize stuff further with json :3c

json goes in geodes config folder, in a folder named **"nwo5.group_labels"** (click the folder icon in the geode menu and if you dont see a folder called **"config"** go back 1 folder in the hierarchy then u should see it)

### Label Types
you have to set the `label type` setting to json for this to work btw

```
// label-types.json

{
    "OBJECT ID": {
        "type": "TYPE"
    },
    "OBJECT ID": {
        "type": "TYPE"
    }
}
```

valid types are:
- "center"
- "target_center"
- "target-center"
- "item"
- "item_anim"
- "anim_target-center"
- "target-center_item-item2"
- "target_item-item2"
- "item_target"
- "target_item"
- "gradient"
- "enter"
- "sfx"
- "color"
- "pulsecolor"
- "blacklist" (adds the trigger to the blacklist, meaning group labels wont show for this trigger)

anything without any entry defaults to just showing target group

type names are formatted like topleft-topright_bottomleft-bottomright, if theres only one on either the top or bottom its centered, if not theyre side by side

### Extras Colors
you have to set `json for extras` setting to true for this to work btw

```
// extras-colors.json

{
    "TYPE": {
        "off-color": [0, 0, 0],
        "off-opacity": 0,
        "on-color": [255, 255, 255],
        "on-opacity": 255
    }
}
```

valid types are:
- "activate"
- "control-id"
- "blending"
- "pulse-target-type" 
- "override"
- "follow"

also you have to have all 4 properties of a type for to actually change

if you dont define something valid for a type its just the default

btw some presets are in the github repo for this mode in a folder called presets

## Credits
- ***farp3*** for the no rotate idea
- ***sandboxer*** for the *"add group labels to stuff that should really have group labels but dont for some reason"* idea
- ***alphalaneous*** most the reason v1.0.1 and v1.0.2 and v1.0.3 exist thxxxx

## Quote
***"*** *this is one of those suggestions where people go "i think the new car from 2.2 should have windows on the doors" and i go "what the fuck do you mean the new car from 2.2 doesn't already have windows on the doors" and then i check and it turns out indeed the new car from 2.2 has no windows on the doors* ***"*** - ***HJfod***