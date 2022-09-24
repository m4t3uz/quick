#include <templatizer.h>
#include <libical/ical.h>

static int init(struct context *data, struct templatizer_callbacks *cb)
{
	const char *text = "";
	char *path;
	char *method;
	int result;

	cb->set_output_format(data, TMPL_FMT_HTML);
	cb->send_default_headers(data);
	puts("<!DOCTYPE html>");
	method = getenv("REQUEST_METHOD");
	{
	icalcomponent *event;
	icalproperty *prop;
	icalparameter *param;
	struct icaltimetype atime;

	/* create new VEVENT component */
	event = icalcomponent_new(ICAL_VEVENT_COMPONENT);

	/* add DTSTAMP property to the event */
	prop = icalproperty_new_dtstamp(atime);
	icalcomponent_add_property(event, prop);

	/* add UID property to the event */
	prop = icalproperty_new_uid("guid-1.example.com");
	icalcomponent_add_property(event, prop);

	/* add ORGANIZER (with ROLE=CHAIR) to the event */
	prop = icalproperty_new_organizer("mrbig@example.com");
	param = icalparameter_new_role(ICAL_ROLE_CHAIR);
	icalproperty_add_parameter(prop, param);
	icalcomponent_add_property(event, prop);
	}
	return 0;
}

static void quit() {}

struct templatizer_plugin templatizer_plugin_v1 = {
	&init,
	&quit
};

