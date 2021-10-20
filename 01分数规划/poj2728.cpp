double l=0.0,r=1.0,mid;
while (r-l>eps)
{
	mid=(l+r)/2;
	for (int i=1;i<=n;i++) d[i]=a[i]-mid*b[i];
	sort(d+1,d+1+n);
	double sum=0.0;
	for (int i=k+1;i<=n;i++) sum+=d[i];
	if (sum>0) l=mid;
	else r=mid;
}
